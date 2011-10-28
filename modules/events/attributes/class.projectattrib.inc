<?php
/**
 * This file is part of the Achievo distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * @package achievo
 * @subpackage events
 *
 * @copyright (c)2008 Ibuildings B.V.
 * @license http://www.achievo.org/licensing Achievo Open Source License
 *
 * @version $Revision: 5102 $
 * $Id: class.eventsattrib.inc 5102 2008-07-04 13:39:14Z sandy $
 */
define("AF_FORMSUBMIT", AF_SPECIFIC_1);

/**
 * Phase dependency attribute
 * 
 * @package achievo
 * @subpackage events
 */
class atkProjectAttribute extends atkAttribute
{
  /**
   * Constructor
   * @param $name Name of the attribute
   * @param $flags Flags for this attribute
   */
  function atkProjectAttribute($name, $flags=0)
  {
    /* base class constructor */
    $this->atkAttribute($name, $flags);
  }

  /**
   * Returns a piece of html code that can be used in a form to edit this
   * attribute's value.
   * @param $record array with fields
   * @return string piece of html code with a textarea
   */
  function edit($record="")
  {
    $selectedeventsid = atkArrayNvl($_REQUEST, "selectedeventsid", "");

    // The current phase (in case of edit of an existing record)
    $currentevents = $record[$this->fieldName()];
    if (is_array($currentevents)) $currentevents = $currentevents["eventsid"];

    // The current value might be overriden by use of the 'search all phases' button
    if (isset($selectedeventsid)&&$selectedeventsid!="")
    {
      $currentevents = $selectedeventsid;
    }

    $eventss = $this->getRecentProjects();
    $eventsarray = Array();

    $alreadyadded = false;

    // Check if the currently selected events is already in the recent list.
    for ($i=0;$i<count($eventss);$i++)
    {
      if ($eventss[$i]['id']==$currentevents)
      {
        $alreadyadded = true;
      }
    }

    // if not already added (by the recent list), we have to load it manually.
    if (!$alreadyadded&&$currentevents!="")
    {
      $events = $this->getProject($currentevents);
      $eventss[] = $events;
    }

    $result = '<select name="eventsid">';
    $result.= '<option value="">'.atktext('select');

    for ($i=0;$i<count($eventss);$i++)
    {
      $result .= '<option value="'.$eventss[$i]["id"].'" ';

      // de juiste default selecteren
      if ($eventss[$i]["id"]==$currentevents) $result.="selected";

      $result .= '>'.$eventss[$i]["name"];
    }

    $result .= '</select>&nbsp';

    $targeturl = atkSelf()."?selectedeventsid=[id]&atklevel=".atkLevel();

    if ($this->hasFlag(AF_FORMSUBMIT)) $submit = true; else $submit = false;
    $result .= href(dispatch_url("events.events", "select", array("atkfilter" => "events.status='active'", "atktarget" => $targeturl)), atktext("searchalleventss"),SESSION_NESTED, $submit);

    return $result;
  }

  /**
   * Display events name
   *
   * @param array $rec Record
   * @return string
   */
  function display($rec)
  {
    return $rec[$this->fieldName()]["projname"];
  }

  /**
   * Database to value
   *
   * @param array $rec Record
   * @return array
   */
  function db2value($rec)
  {
    return Array("projname"=>$rec["proj_name"], "eventsid"=>$rec["eventsid"]);
  }

  /**
   * Add to query
   *
   * @param atkQuery $query Query
   * @param string $tablename Tablename
   * @param string $fieldaliasprefix Field alias prefix
   * @param array $rec Record
   * @param int $level Level
   * @param string $mode Mode
   */
  function addToQuery(&$query, $tablename="", $fieldaliasprefix="", $rec="", $level=0, $mode="")
  {
    if ($mode == "select" || $mode == "admin")
    {
      //$query->addField($this->fieldName(),"","hours",$fieldaliasprefix,!$this->hasFlag(AF_NO_QUOTES));
      $query->addField("name","", "B", "proj_", false);
      $query->addField("eventsid","", "costregistration", "", false);
      //$query->addField("name","", "A", "phase_", false);
      //$query->addField("name","", "C", "activity_", false);
      //$query->addJoin("activity", "C", "C.id=hours.activityid", false);
      //$query->addJoin("phase", "A","A.id=hours.phaseid", true);
      $query->addJoin("events", "B","B.id=costregistration.eventsid", true);

    }

    else if ($mode == "add" || $mode == "edit")
      $query->addField($this->fieldName(),$this->value2db($rec),"","",!$this->hasFlag(AF_NO_QUOTES));
  }

  /**
   * Get recent eventss
   *
   * @return array
   */
  function getRecentProjects()
  {
    global $g_user;

    $db = &atkGetDb();

    $query = "SELECT events.name as name, events.id as id FROM events,phase,hours ";
    $query.= "WHERE phase.id=hours.phaseid AND userid='".$g_user["id"]."'
                AND phase.status='active'
                AND events.status<>'archived'
                AND phase.eventsid=events.id ";
    $query.= "ORDER BY hours.entrydate DESC";

    // 100 should be enough to get 5 unique recent eventss.
    $arr = $db->getrows($query,'0','100');
    $j=0;
    $alreadyhad = Array();
    $newarr = Array();
    for ($i=0;$i<count($arr)&&$j<$GLOBALS["config_numberofrecenteventss"];$i++)
    {
      if (!in_array($arr[$i]['id'],$alreadyhad))
      {
        $alreadyhad[$j]=$arr[$i]['id'];
        $newarr[$j]['id'] = $arr[$i]['id'];
        $newarr[$j]['name'] = $arr[$i]['name'];
        $j++;
      }
    }
   return $newarr;
  }

  /**
   * Get events id and name
   *
   * @param int $eventsid Project id
   * @return array
   */
  function getProject($eventsid)
  {
    $db = &atkGetDb();

    $query = "SELECT id,name FROM events ";
    $query.= "WHERE id = $eventsid ";

    $arr = $db->getrows($query);

    $events = $arr[0];
    return $events;
  }

}
?>
