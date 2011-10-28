<?php

  /**
   * Project extension with a custom action to remove the events from a contract.
   *
   * @author Ivo Jansch <ivo@achievo.org>
   * @version $Revision: 2385 $
   *
   * $Id: class.contract_events.inc 2385 2007-09-17 09:33:11Z guido $
   */

  include_once(moduleDir("events")."class.events.inc"); // include original baseclass.

  class contract_events extends events
  {
    function contract_events()
    {
      $this->events();
      $this->m_flags |= NF_NO_FILTER;;
      $this->m_type = "contract_events";
      $statusattr = &$this->getAttribute("status");
      $statusattr->addFlag(AF_FORCE_LOAD);
      $customerattr = &$this->getAttribute("customer");
      $customerattr->setForceInsert(true);

      // Anyone who may edit contracts, may remove a events from the deposit.
      $this->m_securityMap["remove"] = "contracts.edit";

      // The rest of the actions has equal privileges to the original node.
      $this->setSecurityAlias("events.events");

      //clear parent filters.
      $this->m_fuzzyFilters = array();
      $this->m_filters = array();
    }

    /**
     * Remove a events from a contract.
     */
    function action_remove(&$handler)
    {
      if ($this->m_postvars["events_id"]!="")
      {
        $db = &atkGetDb();
        $db->query("UPDATE events SET contract_id = NULL WHERE id = '".$this->m_postvars["events_id"]."'");
      }
      $this->redirect();
    }

    function recordActions($record, &$actions, &$mraactions)
    {
    	$actions = array(); // Remove all default actions.
      if ($this->allowed("remove", $record)) $actions["remove"] = dispatch_url($this->atkNodeType(), "remove", array("events_id"=>$record["id"]));
      if ($this->allowed("view", $record)) $actions["view"] = dispatch_url("events.events", "view", array("atkselector"=>$this->primaryKey($record)));
      if ($this->allowed("edit", $record)) $actions["edit"] = dispatch_url("events.events", "edit", array("atkselector"=>$this->primaryKey($record)));
    }

    function initial_values()
    {
      $forceList = (isset($this->m_postvars['atkfilter'])) ? decodeKeyValueSet($this->m_postvars['atkfilter']) : array();
      $node = &atkGetNode("organization.contracts");
      $selector = sprintf("`contract`.`id`='%d'", $forceList["contract_id.id"]);
      $rec = $node->selectDb($selector, "", "", "", array("contractname", "customer"));
      $initial_values = parent::initial_values();
      $initial_values["name"] = $rec[0]['contractname'];
      $initial_values["customer"] = $rec[0]['customer'];
      return $initial_values;
    }
  }

?>