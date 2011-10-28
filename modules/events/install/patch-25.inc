<?php
$setup->createIndex('events','name',array('fields'=>array('name'=>array('sorting' => 'ascending',                                           
                                                                         'length' => 25                                                      
                                                                         ))));
                                                                         
$setup->createIndex('phase','events_id',array('fields'=>array('eventsid'=>array('sorting' => 'ascending',                                           
                                                                         'length' => ''                                                      
                                                                         ))));
                                                                         
?>