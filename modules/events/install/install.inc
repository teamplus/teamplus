<?php

  $setup->installNode("events.activity");
  $setup->installNode("events.phase");
  $setup->installNode("events.phase_activity");
  $setup->installNode("events.phaseplanning");
  $setup->installNode("events.events");
  $setup->installNode("events.events_personcontact");
  $setup->installNode("events.events_personemployee");
  $setup->installNode("events.role");
  $setup->installNode("events.dependency");
  $setup->installNode("events.tpl_phase");
  $setup->installNode("events.tpl_phase_activity");
  $setup->installNode("events.tpl_events");
  $setup->installNode("events.tpl_events_phase");
  $setup->installNode("events.tpl_dependency");
  $setup->installNode("events.deliverable");
  $setup->installNode("events.mastergantt_colorconfig");
  $setup->installNode("events.events_category");
  
  $setup->createIndex('events','name',array('fields'=>array('name'=>array('sorting' => 'ascending',                                           
                                                                           'length' => 25                                                      
                                                                           ))));
                                                                           
  $setup->createIndex('phase','events_id',array('fields'=>array('eventsid'=>array('sorting' => 'ascending',                                           
                                                                         'length' => ''                                                      
                                                                         ))));

  $setup->setVersion(25);

?>
