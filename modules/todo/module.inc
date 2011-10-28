<?php
/**
 * This file is part of the Achievo distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * @package achievo
 * @subpackage todo
 *
 * @copyright (c)2008 Ibuildings B.V.
 * @license http://www.achievo.org/licensing Achievo Open Source License
 *
 * @version $Revision: 5512 $
 * $Id: module.inc 5512 2009-03-21 12:00:50Z sandy $
 */


  /**
   * Module file for the menu items and security
   *
   * @package achievo
   * @subpackage todo
   */
  class mod_todo extends achievoModule
  {
    function getNodes()
    {
      registerNode("todo.todo", array("admin", "add", "edit", "delete"));
      registerNode("todo.todo_history",array('view'));
    }

    function getMenuItems()
    {
      $selectedevents = array_key_exists("selectedevents", $_REQUEST) ? $_REQUEST["selectedevents"] : 0;
      if ($selectedevents == 0)
      {
        $this->menuitem("events_todoview", dispatch_url("todo.events_todoview", "admin"), "eventsmanagement", array("todo.todo", "admin"));
      }
      else
      {
        $this->menuitem("events_todoview", dispatch_url("todo.events_todoview", "edit", array("atkselector" => "events.id=".$selectedevents)), "eventsmanagement", array("todo.todo", "admin"));
      }
    }

    function getDependencies($mode)
    {
      return array("events");
    }


    function getPimItems()
    {
      return array("todos"=>"getTodo");
    }

    function getTodo()
    {
      include_once(moduleDir("todo")."pim.inc");
      return pimTodos();
    }
  }

?>