<?php
  /**
   * contacteventsslist node class file
   *
   * @package achievo
   * @subpackage modules
   *
   * @author guido <guido@ibuildings.nl>
   *
   * @copyright (c) 2006 Ibuildings.nl BV
   * @license http://www.achievo.org/atk/licensing/ ATK open source license
   * @license http://www.gnu.org/copyleft/gpl.html GNU General Public License 2
   *
   * @version $Revision: 1803 $
   * $Id: class.contacteventsslist.inc 1803 2006-08-01 13:25:26Z guido $
   */

  /**
   * @internal Load used classes
   */
  useattrib("atkdummyattribute");

  /**
   * The node class for contacteventsslist.
   *
   * @author guido <guido@ibuildings.nl>
   * @package achievo
   * @subpackage modules
   */
  class contacteventsslist extends atkDummyAttribute
  {

    var $m_status = "active";

    /**
     * contacteventsslist constructor
     */
    function contacteventsslist($name, $status="active", $flags=0)
    {
      $this->atkDummyAttribute($name, "", $flags|AF_DUMMY_SHOW_LABEL);
      $this->m_status = $status;
    }

    /**
     * Returns a html recordlist of eventss
     *
     * @param unknown_type $record
     * @param unknown_type $mode
     * @return unknown
     */
    function showProjects($record, $mode)
    {
      $eventsnode = &atkGetNode("events.events");
      useattrib("events.filtereventsbycontactattrib");
      $eventsnode->add(new filterProjectByContactAttrib($record["id"]));
      $eventsnode->m_fuzzyFilters=array("events.status='".$this->m_status."'");
      $recs = $eventsnode->selectDb("", "", "", $eventsnode->m_listExcludes);
      if (count($recs)>0)
      {
        $rl = &atknew("atk.recordlist.atkrecordlist");
        return $rl->render($eventsnode, $recs, $eventsnode->defaultActions($mode), RL_NO_SEARCH|RL_NO_SORT);
      }
      return atktext("none");
    }

    /**
     * Edit  record
     * Here it will only return the text, no edit box.
     * @param $record Array with fields
     * @return Parsed string
     */
    function edit($record="", $fieldprefix="")
    {
      return $this->showProjects($record, "relation");
    }

    /**
     * Display a record
     * Here it will only returns the text.
     * @param $record  Array with fields
     * @return Parsed string
     */
    function display($record)
    {
      return $this->showProjects($record, "view");
    }


  }
?>