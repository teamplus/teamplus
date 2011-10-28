<?php

  // TODO: this script uses installNode calls.
  // This is not allowed for conversion script, since the nodes refered to 
  // might disappear or change in later releases, leaving this conversion 
  // script crippled.
  // The calls must be replaced by create table and/or alter table statements.

  $setup->report("Start conversion of 0.9.1 database -> 0.9.2 database");
  
  atkdebug("In convert-0.9.1-to-0.9.2.inc");
  
  // Declare a utility function for converting varchar userid's to the new int
  // foreign keys for users.
  function useridConvert($table, $field, $setup)
  {
    static $s_users="";
    $db = &atkGetDb();
    
    // One time retrieval of all employees.
    if ($s_users=="")
    {
      $sql = "SELECT id, userid FROM person WHERE role='employee'";
      $s_users = $db->getrows($sql);
    }
    
    if (count($s_users) > 0)
    {
      for ($i=0;$i<count($s_users);$i++)
      {                
        $db->query("UPDATE $table SET $field='".$s_users[$i]["id"]."' WHERE $field = '".$s_users[$i]["userid"]."'");
      }
    }    
    $setup->alterColumn($table, $field, $field, "int(10)", false);    
    
  }
  
  $setup->installNode("setup.versioninfo");
 
  // Create the schedule_notes table.
  //$setup->installNode("calendar.schedule_notes");

  //convert contact table to person table and copy employees to person table
  $setup->renameTable("contact", "person");
  $setup->dropColumn("person", "owner"); // no longer used.
  
  // The following calls will add new fields to the person table.
  $setup->addColumn("person", "state", "varchar(100)");
  $setup->addColumn("person", "function", "varchar(50)");
  $setup->addColumn("person", "role", "varchar(15)", false);
  $setup->addColumn("person", "entity", "int(10)");
  $setup->addColumn("person", "supervisor", "varchar(15)"); // make it a varchar first to allow employee table conversion
  $setup->addColumn("person", "status", "varchar(9)");
  $setup->addColumn("person", "userid", "varchar(15)", false);
  $setup->addColumn("person", "password", "varchar(40)");
  
  $setup->addColumn("person", "theme", "varchar(15)");
  
  // Also update the usercontract node.
  $setup->addColumn("usercontract", "workingdays", "varchar(14)");
  
  // Create events_person table with all necessary fields.
  $setup->installNode("events.events_personcontact");
  $setup->installNode("events.events_personemployee");
 
  //set role = "contact" for all persons in person table
  //these persons are only contacts at this moment  
  $db->query("UPDATE person SET role = 'contact' WHERE role IS NULL OR role=''");  

  //copy employees to persons table  
  $employees = $db->getrows("SELECT * FROM employee");

  if (count($employees)>0)
  {
    for ($j=0;$j<count($employees);$j++)
    {      
      $id = $db->nextid("person");
      
      // Assume names are in the format 'Jay Random Hacker'.
      // Firstname will become 'Jay', Lastname will become 'Random Hacker'.
      $names = explode(" ", $employees[$j]["name"]);
      $firstname = array_shift($names);
      $lastname = implode(" ", $names);
      
      $db->query("INSERT INTO person (id, 
                                        userid, 
                                        password, 
                                        lastname, 
                                        firstname, 
                                        email, 
                                        supervisor, 
                                        status, 
                                        theme, 
                                        entity, 
                                        role)
                                VALUES ('$id', 
                                        '".$employees[$j]["userid"]."', 
                                        '".$employees[$j]["password"]."', 
                                        '".$lastname."', 
                                        '".$firstname."',
                                        '".$employees[$j]["email"]."', 
                                        '".$employees[$j]["supervisor"]."', 
                                        '".$employees[$j]["status"]."', 
                                        '".$employees[$j]["theme"]."',
                                        '".$employees[$j]["entity"]."', 
                                        'employee')");      
    }

  }

  //drop employee table
  $setup->dropTable("employee");  

  //rename customer table to organization
  $setup->renameTable("customer", "organization");
    
  // Update the organization node with new fields.
  $setup->addColumn("organization", "state", "varchar(100)");

  $setup->installNode("events.role");  

  //insert roles in table role  
  $res = $db->query("INSERT INTO role (id, name) VALUES (1, 'Developer')");    
  $res = $db->query("INSERT INTO role (id, name) VALUES (2, 'Customer')");  
  $res = $db->query("INSERT INTO db_sequence (seq_name, nextid) VALUES ('role', 2)");  

  //copy contact of a events into events_person
  $sql = "SELECT events.* FROM events";
  $eventss = $db->getrows($sql);
 
  $customer_defaultcontacts = array(); 
  $contact_obligatory = atkconfig("events_contact_obligatory",false);
  for ($i=0;$i<count($eventss);$i++)
  {  
    if ($eventss[$i]["contact"] != 0)
    {     
      $db->query("INSERT INTO events_person (personid, eventsid, role)
                         VALUES ('".$eventss[$i]["contact"]."', '".$eventss[$i]["id"]."', 2)");      
    }
    else
    {    
      if ($eventss[$i]["customer"]!=0 && $contact_obligatory) // if customer is not set or contact is not obligatory, we don't need to convert
      {
        // events has a customer, but a contact person was not set. Create a default contact person.        
        if (empty($customer_defaultcontacts[$eventss[$i]["customer"]])) // check if we already added a default contact for this customer.
        {
        
          $id = $db->nextid("person");
          $db->query("INSERT INTO person (id, 
                                            firstname,
                                            lastname, 
                                            company, 
                                            role)
                                    VALUES ('$id', 
                                            '(please update)',
                                            'Auto-generated default contact', 
                                            '".$eventss[$i]["customer"]."', 
                                            'contact')");      
          $customer_defaultcontacts[$eventss[$i]["customer"]] = $id;          
        }
        $db->query("INSERT INTO events_person (personid, eventsid, role)
                       VALUES ('".$customer_defaultcontacts[$eventss[$i]["customer"]]."', '".$eventss[$i]["id"]."', 2)");          
      }      
    }
  }
  
  $defaultcnt = count($customer_defaultcontacts);
  if ($defaultcnt>0)
  {  
    $setup->report("For ".$defaultcnt." customer".($defaultcnt>1?"s":"")." a 
                    new auto-generated contact person was added to be part of 
                    eventss that did not have a contactperson yet. ".($defaultcnt>1?"These 
                    contacts have":"This contact has")." been named 'Auto-generated default 
                    contact'. Please update this name to the correct value.", "important");
  }

  $setup->dropColumn("events", "contact");
  
  //add new fields to schedule table
  $setup->addColumn("schedule", "all_users", "int(1)");
  $setup->addColumn("schedule", "status", "varchar(11)");
  
  atkdebug("After last installnode");
     
  $setup->renameTable("schedule_attendees", "schedule_attendee");
  
  $setup->alterColumn("schedule_attendee", "scheduleid", "schedule_id", "int(10)", false);
  $setup->alterColumn("schedule_attendee", "userid", "person_id", "int(10)", false);        

  $setup->renameTable("schedule_types", "schedule_type");
    
  // employee_events records will be converted to events_person
  $sql = "SELECT employeeid FROM employee_events";
  $res = $db->getrows($sql);
  if (count($res) > 0)
  {
    for ($i=0;$i<count($res);$i++)
    {
      //search employee id with given userid      
      $result = $db->getrows("SELECT id FROM person WHERE userid ='".$res[$i]["employeeid"]."' AND role='employee'");
      $db->query("UPDATE employee_events SET employeeid='".$result[0]["id"]."' WHERE employeeid = '".$res[$i]["employeeid"]."'");
    }
  }

  //copy all employees to the events_person table  
  $eventss = $db->getrows("SELECT * FROM employee_events");
  for ($i=0;$i<count($eventss);$i++)
  {
    $db->query("INSERT INTO events_person (personid, eventsid, role)
                       VALUES ('".$eventss[$i]["employeeid"]."', '".$eventss[$i]["eventsid"]."', 1)");    
  }
  
  $setup->dropTable("employee_events");    
  
  //convert planning, employee_events, rate, usercontract, person, todo, todo_history and events table because this version
  //does not use userid as primary key for employees    
  useridConvert("hours", "userid", $setup);
  useridConvert("events", "coordinator", $setup);
  useridConvert("events_person", "personid", $setup);
  useridConvert("events_notes", "owner", $setup);
  useridConvert("usercontract", "userid", $setup);  
  useridConvert("person", "supervisor", $setup); 
  useridConvert("todo", "assigned_to", $setup);  
  useridConvert("todo", "owner", $setup);  
  useridConvert("todo_history", "assigned_to", $setup);
  useridConvert("todo_history", "owner", $setup);
  useridConvert("schedule", "owner", $setup);
  
  // Add new id field to hours_lock table.
  $setup->addColumn("hours_lock", "id", "int(10)", false);
 
  // We must give all records a unique value to be able to use the id
  // field as a primary key.
  $recs = $db->getrows("SELECT * FROM hours_lock");
  for ($i=0, $_i=count($recs); $i<$_i; $i++)
  {
    $db->query("UPDATE hours_lock 
                     SET id=".($i+1)." 
                   WHERE userid='".$recs[$i]["userid"]."' 
                     AND week='".$recs[$i]["week"]."'");
  }
  $res = $db->query("INSERT INTO db_sequence (seq_name, nextid) VALUES ('hours_lock', $i)");  
  
  $db->query("ALTER TABLE hours_lock DROP PRIMARY KEY, ADD PRIMARY KEY(id)");  
  $db->query("UPDATE hours_lock SET userid = '' WHERE userid='*'"); // We can't set it to null
                                                                      // yet, but we must remove
                                                                      // the '*' values to be
                                                                      // able to convert it to int
  useridConvert("hours_lock", "userid", $setup);    
  $setup->alterColumn("hours_lock", "userid", "userid", "int(10)", true); // for hours_lock, the userid field may be null  
  $db->query("UPDATE hours_lock SET userid = NULL WHERE userid=''");
  
  
  // Perform some additional alterations to make db more compatible
  // with fresh 0.9.2+ installs.
  $setup->alterColumn("accessright", "node", "node", "varchar(100)", false);
  $setup->alterColumn("accessright", "entity", "entity", "int(10)", false);
  $setup->alterColumn("activity", "id", "id", "int(10)", false);
  $setup->alterColumn("activity", "remarkrequired", "remarkrequired", "int(1)", true);
  $setup->alterColumn("activity", "description", "description", "varchar(50)", true);  
  $setup->alterColumn("db_sequence", "seq_name", "seq_name", "varchar(40)", false);
  $setup->alterColumn("db_sequence", "nextid", "nextid", "int(10)", false);
  $setup->alterColumn("hours", "id", "id", "int(10)", false);
  $setup->alterColumn("hours", "activityid", "activityid", "int(10)", false);
  $setup->alterColumn("hours", "phaseid", "phaseid", "int(10)", false);
  $setup->alterColumn("hours", "time", "time", "int(10)", false);
  //$setup->dropColumn("hours", "ratetype"); // no longer used.
  $setup->alterColumn("events", "id", "id", "int(10)", false);
  $setup->alterColumn("events", "status", "status", "varchar(15)", true);   
  $setup->alterColumn("events", "description", "description", "text", true);   
  $setup->alterColumn("events", "coordinator", "coordinator", "int(10)", true);   
  $setup->alterColumn("contract", "contracttype", "contracttype", "int(10)", false);
  $setup->alterColumn("contract", "billing_period", "billing_period", "varchar(12)", false);  
  $setup->alterColumn("contract", "id", "id", "int(10)", false);
  $setup->alterColumn("contract", "description", "description", "text", false);
  $setup->alterColumn("usercontract", "id", "id", "int(10)", false);
  $setup->alterColumn("contracttype", "id", "id", "int(10)", false);
  $setup->alterColumn("organization", "id", "id", "int(10)", false);
  $setup->alterColumn("organization", "address", "address", "varchar(100)", true);
  $setup->alterColumn("organization", "zipcode", "zipcode", "varchar(20)", true);
  $setup->alterColumn("organization", "city", "city", "varchar(100)", true);
  $setup->alterColumn("organization", "state", "state", "varchar(100)", true);
  $setup->alterColumn("organization", "country", "country", "varchar(100)", true);
  $setup->alterColumn("organization", "phone", "phone", "varchar(20)", true);
  $setup->alterColumn("organization", "fax", "fax", "varchar(20)", true);
  $setup->alterColumn("organization", "email", "email", "varchar(50)", true);
  $setup->alterColumn("organization", "remark", "remark", "text", true);
  $setup->alterColumn("organization", "bankaccount", "bankaccount", "varchar(30)", true);
  $setup->alterColumn("person", "id", "id", "int(10)", false);
  $setup->alterColumn("person", "firstname", "firstname", "varchar(50)", true);
  $setup->alterColumn("person", "lastname", "lastname", "varchar(50)", false);
  $setup->alterColumn("person", "supervisor", "supervisor", "int(10)", true);  
  $setup->alterColumn("person", "address", "address", "varchar(100)", true);
  $setup->alterColumn("person", "zipcode", "zipcode", "varchar(20)", true);
  $setup->alterColumn("person", "city", "city", "varchar(100)", true);
  $setup->alterColumn("person", "country", "country", "varchar(100)", true);
  $setup->alterColumn("person", "phone", "phone", "varchar(20)", true);
  $setup->alterColumn("person", "fax", "fax", "varchar(20)", true);
  $setup->alterColumn("person", "email", "email", "varchar(50)", true);
  $setup->alterColumn("person", "remark", "remark", "text", true);
  $setup->alterColumn("person", "company", "company", "int(10)", true);
  $setup->alterColumn("phase", "id", "id", "int(10)", false);
  $setup->alterColumn("phase", "status", "status", "varchar(9)", true); 
  $setup->alterColumn("phase", "max_phasetime", "max_phasetime", "int(10)", true); 
  $setup->alterColumn("phase", "max_hours", "max_hours", "int(10)", true); 
  $setup->alterColumn("phase", "description", "description", "text", true); 
  $setup->dropColumn("phase_activity", "billable"); // no longer used
  $setup->alterColumn("phase_activity", "phaseid", "phaseid", "int(10)", false);
  $setup->alterColumn("phase_activity", "activityid", "activityid", "int(10)", false);
  $setup->alterColumn("profile", "id", "id", "int(10)", false);
  $setup->alterColumn("events_notes", "id", "id", "int(10)", false);
  $setup->alterColumn("events_notes", "eventsid", "eventsid", "int(10)", false);
  $setup->alterColumn("events_notes", "description", "description", "text", false);
  $setup->alterColumn("schedule", "id", "id", "int(10)", false);
  $setup->alterColumn("schedule_type", "id", "id", "int(10)", false);
  //$setup->alterColumn("schedule_note", "owner", "owner", "int(10)", false);
  //$setup->alterColumn("schedule_note", "schedule_id", "schedule_id", "int(10)", false);
  $setup->alterColumn("todo", "id", "id", "int(10)", false);
  $setup->alterColumn("todo", "eventsid", "eventsid", "int(10)", false);
  $setup->alterColumn("todo", "status", "status", "int(1)", false);
  $setup->alterColumn("todo", "assigned_to", "assigned_to", "int(10)", true);
  $setup->alterColumn("todo", "priority", "priority", "int(1)", false);
  $setup->alterColumn("todo", "description", "description", "text", false);
  $setup->alterColumn("todo_history", "id", "id", "int(10)", false);
  $setup->alterColumn("todo_history", "todoid", "todoid", "int(10)", false);
  $setup->alterColumn("todo_history", "eventsid", "eventsid", "int(10)", false);
  $setup->alterColumn("todo_history", "description", "description", "text", false);
  $setup->alterColumn("todo_history", "status", "status", "int(1)", false);
  $setup->alterColumn("todo_history", "priority", "priority", "int(1)", false);
  $setup->alterColumn("todo_history", "assigned_to", "assigned_to", "int(10)", true);
  $setup->alterColumn("todo_history", "updated", "updated", "datetime ", true);
  $setup->alterColumn("tpl_phase_activity", "phaseid", "phaseid", "int(10)", false);
  $setup->alterColumn("tpl_phase_activity", "activityid", "activityid", "int(10)", false);
  $setup->alterColumn("tpl_phase", "description", "description", "text", true);
  $setup->alterColumn("tpl_phase", "id", "id", "int(10)", false);  
  $setup->alterColumn("tpl_events", "id", "id", "int(10)", false);  
  $setup->alterColumn("tpl_events", "description", "description", "text", true);  
 
  //change the node rights in the accessright table to this format: modulename.nodename
  $db->query("UPDATE accessright SET node = CONCAT('calendar.', node) WHERE node IN ('schedule', 'schedule_types', 'schedule_notes', 'schedule_attendees')");    
  $db->query("UPDATE accessright SET node = CONCAT('costreg.', node) WHERE node = 'costregistration'");  
  $db->query("UPDATE accessright SET node = CONCAT('employee.', node) WHERE node IN ('employee', 'profile', 'usercontracts', 'userprefs')");    
  $db->query("UPDATE accessright SET node = CONCAT('finance.', node) WHERE node IN ('rates', 'finance_customer', 'finance_events', 'billing_events', 'currency', 'bill', 'bill_line')");  
  $db->query("UPDATE accessright SET node = CONCAT('notes.', node) WHERE node IN ('events_notes', 'events_notesview')");    
  $db->query("UPDATE accessright SET node = 'organization.organization' WHERE node = 'customer'");    
  $db->query("UPDATE accessright SET node = CONCAT('organization.', node) WHERE node IN ('contact', 'contracts', 'contracttype')");    
  $db->query("UPDATE accessright SET node = CONCAT('events.', node) WHERE node IN ('events', 'phase', 'activity', 'tpl_phase', 'tpl_events')");  
  $db->query("UPDATE accessright SET node = 'reports.hoursurvey', action='report' WHERE node='hours' AND action='hoursurvey'");
  $db->query("UPDATE accessright SET node = CONCAT('reports.', node) WHERE node IN ('weekreport')");      
  $db->query("UPDATE accessright SET node = CONCAT('resource_planning.', node) WHERE node = 'resource_planning'");    
  $db->query("UPDATE accessright SET node = CONCAT('timereg.', node) WHERE node IN ('hours', 'hours_lock')");  
  $db->query("UPDATE accessright SET node = CONCAT('todo.', node) WHERE node = 'todo'");  
  
  // As of this release, we use version numbers. After running this conversion script, the 
  // database is fully up to date with version 1 of all modules.
  $setup->setVersion("1", "calendar");
  $setup->setVersion("1", "employee");
  $setup->setVersion("1", "notes");
  $setup->setVersion("1", "organization");
  $setup->setVersion("1", "person");
  $setup->setVersion("1", "pim");
  $setup->setVersion("1", "events");
  $setup->setVersion("1", "reports");
  $setup->setVersion("1", "search");
  $setup->setVersion("1", "setup");
  $setup->setVersion("1", "timereg");
  $setup->setVersion("1", "todo");  
  
?>