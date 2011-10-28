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
 * $Id: class.eventsmanytoonerelation.inc 5102 2008-07-04 13:39:14Z sandy $
 */

  userelation("atkmanytoonerelation");

  /**
   * Relation has the same functionality as the normal manytoonerelation,
   * but the attribute itself is not stored in the node.
   *
   * @package modules
   * @subpackage events
   *
   * @author dennis <dennis@ibuildings.nl>
   */
  class eventsManyToOneRelation extends atkManyToOneRelation
  {
    /**
     * Store or not
     *
     * @var boolean
     */
    var $m_store = false;
    /**
     * User id
     *
     * @var int
     */
    var $m_userid = "";

    /**
     * Constructor
     *
     * @param string $name Name
     * @param string $destination Destination
     * @param int $flags Flags
     */
    function eventsManyToOneRelation($name, $destination, $flags=0)
    {
      $this->m_userid = &atkGetUserId();
      if (atkConfig::get("events","events_selection_autocomplete", false))
        $flags |= AF_LARGE;
      parent::atkManyToOneRelation($name, $destination,$flags);
    }

    /**
     * Set Userid
     *
     * @param int $userid User id
     */
    function setUserId($userid)
    {
      $this->m_userid = $userid;
    }

    /**
     * Set store 
     *
     * @param boolean $store Store or not
     */
    function setStore($store=false)
    {
      $this->m_store = $store;
    }

    /**
     * Storage type
     *
     * @param string $mode Mode
     * @return int
     */
    function storageType($mode)
    {
      if($this->m_store == false)
        return NOSTORE;
      else
        return parent::storageType($mode);
    }

    /**
     * Database fieldtype
     *
     * @return string
     */
    function dbFieldType()
    {
      if($this->m_store == false)
        return "";
      else
        return parent::dbFieldType();
    }

    /**
     * Override edit function
     *
     * @param array $record Record
     * @param string $fieldprefix Fieldprefix
     * @param string $mode Mode
     * @return string
     */
    function edit(&$record, $fieldprefix="", $mode="")
    {
      $filter=$this->parseFilter($this->m_destinationFilter,$record);
      $newsel = $this->getHtmlId($fieldprefix);

      $selectionlink = "";
      if(!$this->hasFlag(AF_RELATION_AUTOCOMPLETE))
      {
        $selectionlink = "&nbsp;".$this->createSelectionLink($newsel,$filter);
      }

      return parent::edit($record,$fieldprefix,$mode).$selectionlink;
    }

    /**
     * Creates a link to the selection page of the eventsnode.
     * @param int $id Id
     * @param string $filter Filter
     *
     */
    function createSelectionLink($id,$filter)
    {
      return $this->_getSelectLink($id, $filter);
    }


    /**
     * When the attribute is used as a non-storing attribute, we need to
     * set the join-condition with the phase manually.
     * otherwise, we can use the normal join condition.
     *
     * @param atkquery $query
     * @param String $tablename
     * @param String $fieldalias
     * @return String join condition
     */
    function getJoinCondition(&$query, $tablename="",$fieldalias="")
    {
      if($this->m_store == false)
        return "$fieldalias.id=phaseid.eventsid";

      return parent::getJoinCondition($query,$tablename,$fieldalias);
    }

    /**
     * Get selectable records
     *
     * @param array $record Record
     * @param string $mode Mode
     * @param boolean $force Force
     * @return array
     */
    function getSelectableRecords($record=array(), $mode="",$force=false)
    {
      $newsel = $this->getHtmlId("");
      if(!$this->hasFlag(AF_RELATION_AUTOCOMPLETE))
      {
        //Check if the user has selected another events
        $selectedeventsid = 0;
        if(is_object($this->m_ownerInstance)) //do we have an ownerInstance
        {
          $selectedeventsid = $this->m_ownerInstance->m_postvars[$newsel];
        }

        $eventsids = $this->getRecentProjectsIds($selectedeventsid);
        
        if (!empty($record[$this->fieldName()]["id"]))
          $this->_addProject($record[$this->fieldName()]["id"],$eventsids);
      }

      return $eventsids;
    }

    /**
     * Function returns an array with the events-ids, most recently
     * registered hours on. Number of recent eventss is configurable
     * with the 'config_numberofrecenteventss'.
     *
     * This function also adds the selected events that was returned
     * after selecting a events on the select page of eventss.
     *
     * @param int $selectedeventsid The selected eventsid
     * @return array Project ids
     */
    function getRecentProjectsIds($selectedeventsid=0)
    {
      /* @var $securityManager atkSecurityManager */
      $securityManager = &atkGetSecurityManager();

      /* @var $query atkQuery */
      /* @var $db atkDb */
      $db = &atkGetDb();
      
      $subquery = $db->createQuery();
      $subquery->addTable("hoursbase");
      $subquery->addField("phaseid");
      $subquery->addCondition("hoursbase.userid='".$this->m_userid."'");
      $subquery->addOrderBy("id DESC");
      
      $query = $db->createQuery();

      $query->addTable("phase");

      $query->addField("events.id");
      $query->addField("events.name");
      $query->addField("events.abbreviation");
      
      $query->addJoin("events","","phase.eventsid=events.id",false);
      $query->addJoin("(".$subquery->buildSelect().")","hours","phase.id=hours.phaseid",false);
      $query->addCondition("events.status='active'");

      if (!$securityManager->allowed("timereg.hours", "any_events"))
      {
         $query->addJoin("events_person","","events_person.eventsid = events.id",true);
         $query->addCondition("(events_person.personid = ".$this->m_userid." OR events.timereg_limit = ".PRJ_TIMEREG_ALL_USERS.")");
      }
      
      $query->setLimit(0,atkconfig::get("events","numberofrecenteventss"));
      $arr = $db->getrows($query->buildSelect(true));

      //we add the selected events id on top.
      if(!is_numeric($selectedeventsid))
      {
        $values = decodeKeyValuePair($selectedeventsid);
        $value = $values[$this->m_destInstance->m_table.".".$this->m_destInstance->m_primaryKey[0]];
        if(is_numeric($value) && $value!=0)
        $selectedeventsid = $value;
      }
      $this->_addProject($selectedeventsid,$arr);
      return $arr;
    }

    /**
     * Add events
     *
     * @access private
     * @param int $id Project id
     * @param array $arr Projects array
     */
    function _addProject($id, &$arr)
    {   
      if($id>0)
      {
        $flag = true;
        foreach ($arr as $key=>$value)
        {
          if($value['id'] == $id)
          {
            $flag = false;
            break;
          }
        }
        
        if($flag)
        {
          $db = &atkGetDb();
          $query = $db->createQuery();
          $query->addTable("events");
          $query->addField("events.id");
          $query->addField("events.name");
          $query->addField("events.abbreviation");
          $query->addCondition("id='$id'");
    
          $result = $db->getrows($query->buildSelect());
          $arr = array_merge($result,$arr);
        }
      }
    }

  }
?>
