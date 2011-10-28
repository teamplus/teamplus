<?php

  class mod_reports extends achievoModule
  {    
    function getNodes()
    {
      registerNode("reports.weekreport",array("report","view_all","view_managed"));
      registerNode("reports.hoursurvey",array("report","view_all","view_managed","save_for_all_users"));
      registerNode("reports.eventsstatus",array("report", "any_user"));
      registerNode("reports.eventssurvey",array("report"));
    }

    function pdaNodes()
    {
      return array(
      "hours_hoursurvey"=>dispatch_url("reports.hoursurvey", "report"));
    }

    function getMenuItems()
    {
      $this->menuitem("reports", "","main",true,370);
      // TODO FIXME: hoursurvey is part of timereg.hours class. This should
      // be in a separate class in this module that delegates to the hours class.
      $this->menuitem("hours_hoursurvey", dispatch_url("reports.hoursurvey", "report"),"reports", array("reports.hoursurvey", "report"));
      $this->menuitem("eventssurvey", dispatch_url("reports.eventssurvey", "report"),"reports", array("reports.eventssurvey", "report"));
      $this->menuitem("weekreport", dispatch_url("reports.weekreport", "report"),"reports",array("reports.weekreport","report"));
      $this->menuitem("eventsstatus", dispatch_url("reports.eventsstatus", "report"), "reports", array("reports.eventsstatus", "report"));
    }   
  }

?>