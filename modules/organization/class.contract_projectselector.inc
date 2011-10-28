<?php
	include_once(moduleDir("events")."class.events.inc"); // include original baseclass.
  
  class contract_eventsselector extends events
  {
    function contract_eventsselector($name="contract_eventsselector", $flags=0)
    {
      $this->events($name,$flags);
      //$this->m_filters = array();		//clear parent filters
      
      //only show eventss that are not linked to a contract yet
      $this->addFilter("(events.contract_id IS NULL OR events.contract_id = '')");            
      $this->setSecurityAlias("organization.contracts");
    }
  }
?>