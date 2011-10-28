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
 * $Id: module.inc 5052 2008-06-23 21:18:19Z sandy $
 */


  /**
   * Module file for the menu items and security
   *
   * @package achievo
   * @subpackage notes
   */
  class mod_notes extends achievoModule
  {
    function getNodes()
    {
      registerNode("notes.events_notes", array("admin", "add", "edit", "delete"));
    }

    function getMenuItems()
    {
      $this->menuitem("-","","eventsmanagement");
      $selectedevents = array_key_exists("selectedevents", $_REQUEST) ? $_REQUEST["selectedevents"] : 0;
      if ($selectedevents == 0)
      {
        $this->menuitem("events_notesview", dispatch_url("notes.events_notesview", "admin"), "eventsmanagement", array("notes.events_notes", "admin"));
      }
      else
      {
        $this->menuitem("events_notesview", dispatch_url("notes.events_notesview", "edit", array("atkselector" => "events.id=".$selectedevents)), "eventsmanagement", array("notes.events_notes", "admin"));
      }
    }

    /**
     * Set dependencies for this module
     *
     * @param string $mode Mode
     * @return array Array with dependencies
     */
    function getDependencies($mode)
    {
      return array("events");
    }
  }

?>
