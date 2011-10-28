<?php
  atkdebug("In convert-0.9-to-0.9.1.inc");
  
  $setup->addColumn("events", "abbreviation", "varchar(10)");  
  
  $setup->alterColumn("accessright", "node", "node", "varchar(50)", false);
  $setup->addColumn("todo", "updated", "datetime");

  $db->query("CREATE TABLE employee_events (
                   employeeid varchar(10) NOT NULL default '0',
                   eventsid int(10) NOT NULL default '0',
                   PRIMARY KEY  (employeeid,eventsid)
                )");

  $db->query("CREATE TABLE todo_history (
                   id int(10) DEFAULT '0' NOT NULL,
                   todoid int(10) DEFAULT '0' NOT NULL,
                   updated datetime DEFAULT '0000-00-00 00:00' NOT NULL,
                   eventsid int(10) DEFAULT '0' NOT NULL,
                   owner varchar(15) NOT NULL,
                   assigned_to varchar(100) NOT NULL,
                   entrydate date DEFAULT '0000-00-00' NOT NULL,
                   duedate date DEFAULT '0000-00-00' NOT NULL,
                   description text,
                   title varchar(50) NOT NULL,
                   status tinyint(4) DEFAULT '0' NOT NULL,
                   priority tinyint(4) DEFAULT '0' NOT NULL,
                   PRIMARY KEY (id)
                )");

?>