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
   * $Id: class.filtereventsbyorganizationattrib.inc 5102 2008-07-04 13:39:14Z sandy $
   */
      
   useattrib("atkdummyattribute");    

  /**
    * If you add the following attribute to a node that has events information
    * in it (the events node itself, or for example the hoursurvey where events
    * information is loaded as well), then all data can be filtered by an
    * organizationid and a role. The role is optional, you can also filter just
    * by organization.
    *
    * Note that this is a filter-only attribute. It doesn't retrieve any extra
    * information (a feature I might add when needed), and doesn't display anything.
    *
    * @example: 
    *    $eventsnode->add(new filterProjectByOrganizationAttrib(10, 2));
    *    $recs = $eventsnode->selectDb();
    *    In this example, only records will be returned of eventss
    *    where the organization with id 10 has performed role with id 2.
    *    (all eventss where 'Graphic International' acted as 'Designer')    
    *
    * @author Ivo Jansch <ivo@ibuildings.nl>
    * @package achievo
    * @subpackage events
    */
  class filterProjectByOrganizationAttrib extends atkDummyAttribute
  {
    /**
     * Organization id
     * @var int
     */
    var $m_organizationid = NULL;
    /**
     * Project alias
     * @var string
     */
    var $m_eventsalias = NULL;
    /**
     * Role id
     * @var int
     */
    var $m_roleid = NULL;
  
    /**
     * Constructor.
     *
     * @param int organizationid The id of the organization that you wish to 
     *                           filter by.
     * @param int roleid         The id of the role you wish to filter by. 
     *                           This parameter is optional. If you don't 
     *                           pass it, then all records are returned
     *                           that have an association with the specified
     *                           organization.
     * @param string eventsalias This is a hard to understand parameter, 
     *                            which you usually don't need. This is what 
     *                            it does: the attribute filters eventss by
     *                            organization, by hooking itself into the 
     *                            query that the node is going to perform.
     *                            In ordinary cases, the table it needs to 
     *                            join against is called 'events'. But in 
     *                            some occasions, events is present in the
     *                            query with an alias, for example when the
     *                            node does something like 
     *                            'select * from events A, hours B ....'
     *                            In this case, you need to tell the attribute
     *                            that it needs to join against 'A', so you
     *                            pass this as the third parameter.
     */
    function filterProjectByOrganizationAttrib($organizationid, $roleid="", $eventsalias="")
    {
      $this->atkDummyAttribute("custfilter", "", AF_HIDE|AF_FORCE_LOAD);
      $this->m_organizationid = $organizationid;
      $this->m_eventsalias = $eventsalias;
      $this->m_roleid = $roleid;
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
    function addToQuery(&$query, $table="", $aliasprefix="", $rec="", $level, $mode)
    {    
      if (!empty($this->m_organizationid))
      {        
        $query->addJoin("events_person", 
                        "eventsmembers", 
                        (!empty($this->m_eventsalias)?$this->m_eventsalias:"events").".id = eventsmembers.eventsid".
                        (!empty($this->m_roleid)?" AND eventsmembers.role=".$this->m_roleid:""), 
                        true);
        $query->addJoin("person", "person", "person.id = eventsmembers.personid AND person.company='".$this->m_organizationid."'", false);      
        $query->setDistinct(true); // the join we perform could lead to duplicate records.
      }
    }
  } 

?>
