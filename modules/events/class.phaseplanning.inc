<?php

  userelation("atkmanytoonerelation");
  useattrib("atknumberattribute");
  useattrib("atkdurationattribute");
  useattrib("events.spendhoursattribute");  

  class phaseplanning extends atkNode
  {
    function phaseplanning()
    {
      global $g_securityManager;
      
      $this->atkNode("phaseplanning");
      $this->setSecurityAlias("events.phase");
      
      $this->add(new atkManyToOneRelation("phaseid", "events.phase", AF_HIDE|AF_PRIMARY));
      $this->add(new atkManyToOneRelation("personid", "employee.employee", AF_READONLY_EDIT|AF_PRIMARY|AF_FORCE_LOAD));
      $this->add(new atkDurationAttribute("initial_planning",'','', ($g_securityManager->allowed("events.events","initialplanning")?0:AF_READONLY_EDIT)|AF_TOTAL|AF_DURATION_STRING));
      $this->add(new atkDurationAttribute("current_planning",'','', AF_HIDE_ADD|AF_TOTAL|AF_DURATION_STRING));      
      $this->add(new spendHoursAttribute("spend_hours","phaseid",AF_TOTAL));
      
      $this->setTable("events_phaseplanning");
      $this->setOrder("personid.lastname");
    }
    
    function descriptor_def()
    {
      return "[personid.firstname] [personid.lastname]";
    }
    
    function addDb(&$record, $exectrigger=true, $mode="add")
    {
      // This override makes sure that the current_planning is set equal to the number of initial_planning.
      $record["current_planning"] = $record["initial_planning"];
      return parent::addDb($record, $exectrigger, $mode);
    }
    
    function rowColor($record)
    {
      if ($record["current_planning"]>0)
      {
        if($record["spend_hours"]>$record["current_planning"]) 
        {
          return COLOR_ERROR;
        }
        elseif($record["spend_hours"]>=$record["current_planning"]*0.9)
        {
          return COLOR_WARNING;
        }      
      }
    }
    
    function postAdd($rec)
    {
      $db = &atkGetDb();

      $phase_id = $rec["phaseid"]["id"];
      $person_id = $rec["personid"]["id"]; 
      // person may allready exist
      $recs = $db->getrows("SELECT count(*) as cnt 
                              FROM phase, events,events_person
                              WHERE phase.eventsid = events.id
                                AND events.id = events_person.eventsid
                                AND phase.id =$phase_id
                                AND events_person.personid = $person_id
                              GROUP BY events.id");
      if(!count($recs)|| $recs[0]["cnt"]==0)
      {
        $recs = $db->getrows("SELECT events.id FROM phase,events
                                WHERE phase.eventsid = events.id
                                  AND phase.id = $phase_id");
        $events_id = $recs[0]["id"];
        // Add person to members, role will be empty
        $db->query("INSERT INTO events_person (eventsid,personid)
                      values ($events_id,$person_id)");
      }
      
    }
    
    function storePhases($phases)
    {            
      foreach ($phases as $phaseid=>$persons)
      {
        foreach ($persons as $personid=>$current_planning)
        {
          if($phaseid!="" && $personid!="")
          {            
            $recs = $this->selectDb("phaseid='$phaseid' AND personid='$personid'", "", "", "", array("phaseid","personid","initial_planning"));
           
            if (!count($recs))
            {              
              $record = array("phaseid"=>$phaseid, "personid"=>$personid);
              $record["phaseid"] = $this->m_attribList["phaseid"]->db2value($record);
              $record["personid"] = $this->m_attribList["personid"]->db2value($record);
              $record["current_planning"] = $this->m_attribList["current_planning"]->_string2minutes($current_planning);
              $record["initial_planning"]=0;
              if ($record["current_planning"]>0)
              {
                $this->addDb($record);
              }
            }
            else
            {
              $record = $recs[0];
              $record["current_planning"] = $this->m_attribList["current_planning"]->_string2minutes($current_planning);
              $this->updateDb($record);
            }
            
          }
        }
      }
    }
        
  }

?>