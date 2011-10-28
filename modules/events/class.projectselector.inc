<?php

  /**
   * Extension of the events node, with added capabilities of filtering
   * eventss. (members only, etc.)
   */

  include_once(moduleDir("events")."class.events.inc");

  class eventsselector extends events
  {
    function eventsselector()
    {
      $this->events("eventsselector", NF_READONLY);
      $this->setSecurityAlias("events.events");
      $this->add(new eventsFilter());
    }

  }

  class eventsFilter extends atkAttribute
  {
    function eventsFilter()
    {
      $this->atkAttribute("eventsfilter", AF_HIDE|AF_FORCE_LOAD);
    }

    function addToQuery(&$query, $tablename="", $fieldaliasprefix="", $rec="", $level, $mode)
    {
      if ($mode != 'select') return;

      global $g_securityManager;
      if (!$g_securityManager->allowed("timereg.hours", "any_events"))
      {
        $user = getUser();
        $query->addJoin("events_person", "members", "members.eventsid = $tablename.id", true);
        $query->addGroupBy("events.id");
        $query->addCondition("(members.personid = ".$user["id"]." AND $tablename.timereg_limit!=".PRJ_TIMEREG_ALL_USERS.") OR $tablename.timereg_limit=".PRJ_TIMEREG_ALL_USERS);
      }
      $query->addCondition("$tablename.status='active'");
    }
  }

?>
