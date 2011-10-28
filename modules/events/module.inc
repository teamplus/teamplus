<?php

  /**
   * @internal modifiers
   */
  $modifiers[] = "timereg.hours";

  class mod_events extends achievoModule
  {
    function getNodes()
    {
      /* register nodes */
      registerNode("events.events", array("admin", "add", "edit", "delete", "stats","planning", "initialplanning", "any_events", "changeabbreviation"), array("finance", "planning"));
      registerNode("events.phase", array("add", "edit", "delete"));
      registerNode("events.deliverable", array("add", "edit", "delete"));
      registerNode("events.activity", array("admin", "add", "edit", "delete", "stats"));
      registerNode("events.tpl_phase", array("admin", "add", "edit", "delete"));
      registerNode("events.tpl_events", array("admin", "add", "edit", "delete"));
      registerNode("events.role", array("admin", "add", "edit", "delete"));
      registerNode("events.mastergantt_colorconfig", array("admin", "edit"));
    }

    function getMenuItems()
    {
      $selectedevents = array_key_exists("selectedevents", $_REQUEST) ? $_REQUEST["selectedevents"] : 0;
      if ($selectedevents == 0)
      {
        $this->menuitem("eventsmanagement",dispatch_url("events.events", "admin"),"main",array("events.events", "admin"),400); // eventss submenu
        $target_planning = dispatch_url("events.events","planning",array("selectedeventsid"=>"[id]"));
        $this->menuitem("events_admin", dispatch_url("events.events", "admin"), "eventsmanagement", array("events.events", "admin"));
        $this->menuitem("events_planning",  dispatch_url("events.events", "select", array("atktarget" => atkurlencode($target_planning))), "eventsmanagement", array("events.events", "planning"));
        $this->menuitem("-","","eventsmanagement");
        $this->menuitem("events_stats", dispatch_url("events.eventsstats", "stats"), "eventsmanagement", array("events.events", "stats"));
        $this->menuitem("activity_stats", dispatch_url("events.activity", "stats"), "eventsmanagement", array("events.activity", "stats"));
      }
      else
      {
        $this->menuitem("eventsmanagement",dispatch_url("events.events", "admin"),"main",array("events.events", "admin"),400); // eventss submenu
        $this->menuitem("events_edit", dispatch_url("events.events", "edit", array("atkselector" => "events.id='".$selectedevents."'")), "eventsmanagement", array("events.events", "edit"));
        $this->menuitem("events_view", dispatch_url("events.events", "view", array("atkselector" => "events.id='".$selectedevents."'")), "eventsmanagement", array("events.events", "admin"));
        $this->menuitem("events_planning",  dispatch_url("events.events", "planning", array("selectedeventsid" => $selectedevents)), "eventsmanagement", array("events.events", "planning"));
        $this->menuitem("-","","eventsmanagement");
        $this->menuitem("events_stats", dispatch_url("events.eventsstats", "stats", array("eventsid" => $selectedevents)), "eventsmanagement", array("events.events", "stats"));
      }
      $this->menuitem("mastergantt", dispatch_url("events.mastergantt", "planning"), "eventsmanagement", array("events.events", "planning"));
      $this->menuitem("activity_admin", dispatch_url("events.activity", "admin"), "setup", array("events.activity", "admin"));
      $this->menuitem("events_categories", dispatch_url("events.events_category", "admin"), "setup", array("events.activity", "admin"));
      $this->menuitem("tpl_phase_admin", dispatch_url("events.tpl_phase", "admin"), "setup", array("events.tpl_phase", "admin"));
      $this->menuitem("tpl_events_admin", dispatch_url("events.tpl_events", "admin"), "setup", array("events.tpl_events", "admin"));
      $this->menuitem("role_admin", dispatch_url("events.role", "admin"), "setup", array("events.role", "admin"));
      $this->menuitem("mastergantt_colorconfig", dispatch_url("events.mastergantt_colorconfig", "admin"), "setup", array("events.mastergantt_colorconfig", "admin"));
    }

    function getDependencies($mode)
    {
      return array("employee", "organization");
    }

    function search($expression)
    {
      $prjnode = &atkGetNode("events.events");
      return array("eventss"=>$this->recLinks($prjnode->searchDb($expression), "events.events"));
    }

    /**
     * Adds a listener to the timereg.hours node
     *
     * @param hours $atknode hours node instance
     */
    function timereg_hours_modifier(&$node)
    {
      atkimport("module.events.hourslistener");
      $node->addListener(new hoursListener());
    }

  }

?>
