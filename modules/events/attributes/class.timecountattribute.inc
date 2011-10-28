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
 * $Id: class.timecountattribute.inc 5102 2008-07-04 13:39:14Z sandy $
 */
  
/**
 * the timeCountAttribute can be added to the events node (or one of its 
 * derivatives), to add a pseudocolumn with the total number of hours spend
 * on the events.
 * 
 * @package achievo
 * @subpackage events
 */
  class timeCountAttribute extends atkAttribute
  {
    /**
     * Constructor
     *
     * @param int $flags Flags
     */
    function timeCountAttribute($flags=0)
    {
      $this->atkAttribute("timecount", $flags|AF_READONLY|AF_HIDE_ADD);
    }
    
     /**
     * Add field to query
     *
     * @param atkQuery $query ATK Query object
     * @param string $table Tablename
     * @param string $aliasprefix Alias prefix
     * @param array $rec Record
     * @param int $level Level
     * @param string $mode Mode
     */
    function addToQuery(&$query, $tablename="", $fieldaliasprefix="", $rec="", $level, $mode)
    {
      if ($mode!="add"&&$mode!="update")
      {
        $query->addField("sum(hours.time)");        
        $query->addJoin("phase","phase","phase.eventsid = events.id",true);
        $query->addJoin("hours","hours","hours.phaseid = phase.id",true);
        
        $query->addGroupBy("events.id");
      }
    }
    
    /**
     * Database to value
     *
     * @param array $record Record
     * @return int
     */
    function db2value($record)
    {      
      return $record["sum(hours.time)"];
    }
    
    /**
     * Display override
     *
     * @param array $record Record
     * @param string $mode Mode
     * @return string
     */
    function display($record, $mode)
    {
      include_once("achievotools.inc");
      return time_format($record[$this->fieldName()], true);
    }
    
  }

?>