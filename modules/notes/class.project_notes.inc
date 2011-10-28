<?php
/**
 * This file is part of the Achievo distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * @package achievo
 * @subpackage notes
 *
 * @copyright (c)2008 Ibuildings B.V.
 * @license http://www.achievo.org/licensing Achievo Open Source License
 *
 * @version $Revision: 5052 $
 * $Id: class.events_notes.inc 5052 2008-06-23 21:18:19Z sandy $
 */

useattrib("atkdateattribute");
useattrib("atktextattribute");
useattrib("atknumberattribute");
userelation("atkmanytoonerelation");

/**
 * Class for managing events notes
 * @package achievo
 * @subpackage notes
 */
class events_notes extends atkNode
{
  /**
   * Constructor
   */
  function events_notes()
  {
    $this->atkNode("events_notes");

    $this->add(new atkNumberAttribute("id", AF_AUTOKEY));
    $this->add(new atkManyToOneRelation("owner", "employee.employee", AF_HIDE_ADD|AF_READONLY|AF_OBLIGATORY));
    $this->add(new atkManyToOneRelation("eventsid", "events.events",AF_OBLIGATORY|AF_SEARCHABLE|AF_READONLY));
    $this->add(new atkAttribute("title", AF_OBLIGATORY|AF_SEARCHABLE, 50));
    $this->add(new atkDateAttribute("entrydate", "","", date("Ymd"), 0, AF_HIDE_EDIT|AF_HIDE_ADD|AF_OBLIGATORY));
    $this->add(new atkTextAttribute("description" , TEXT_LARGE, AF_OBLIGATORY|AF_HIDE_LIST));
    $this->setTable("events_notes");
    $this->setOrder("entrydate");

  }

  /**
   * Set initial values
   * @return array Array with initial values
   */
  function initial_values()
  {
    global $g_user;
    return array("owner"=>array("id"=>$g_user["id"]),
                 "entrydate"=>array("year"=>date("Y"),
                                    "month"=>date("m"),
                                    "day"=>date("d")));
  }

  /**
   * Set descriptor template
   * @return string
   */
  function descriptor_def()
  {
    return "[title]";
  }
}
?>
