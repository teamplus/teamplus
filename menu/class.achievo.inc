<?php

atkimport("atk.menu.atkframesmenu");

class achievo extends atkFramesMenu
{

  function getHeader($atkmenutop)
  {
    if ($atkmenutop == "eventsmanagement")
    {
      global $g_sessionManager;
      include_once "achievotools.inc";
      $eventss = $g_sessionManager->getValue("selectedprj","globals");

      if (count($eventss) == 0)
      {
        updateSelectedProjects();
        $eventss = $g_sessionManager->getValue("selectedprj","globals");
      }

      $prj  = atktext("events_select") . ':';
      $prj .= '<FORM name="eventsselectorform" action="menu.php" method="get">';
      $prj .= session_form(SESSION_DEFAULT);
      $prj .= '<INPUT type="hidden" name="atkmenutop" value="eventsmanagement">';
      $prj .= '<SELECT style="width: 150px" name="selectedevents" onchange="document.eventsselectorform.submit();">';
      $prj .= '<OPTION value="0">' . atktext("events_select_none") . '</OPTION>';
      $selectedevents = atkArrayNvl($_REQUEST, "selectedevents");
      for ($i=0,$_i=count($eventss); $i<$_i; $i++)
      {
        $selected = ($selectedevents == $eventss[$i]['eventsid']) ? ' selected' : '';
        $prj .= sprintf('<OPTION value="%d" %s>%s</OPTION>', $eventss[$i]['eventsid'], $selected, $eventss[$i]['eventsname']);
      }
      $prj .= '</SELECT></FORM>';
      return $prj;
    }
  }
}

?>