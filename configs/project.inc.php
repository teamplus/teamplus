<?php

  // This variable configures wether hour registrations should be automatically deleted when
  // a phase is deleted. If omitted, false is default.
  $config["events_cascading_delete_hours"] = false;

  // Set a prefix for your initial eventscodes
  // Example: $config["eventscode_prefix"] = "[startdate.year][startdate.month]";
  $config["eventscode_prefix"] = "";

  // If you want an automatic incrementing number to be added to the eventscodes, set this to true
  // Example: $config["eventscode_autonumber"] = true;
  $config["eventscode_autonumber"] = false;

  // Give the automatic incrementing a specific number of digits (the number will be prefixed by zero's)
  // Example: $config["eventscode_autonumberdigits"] = 3;
  $config["eventscode_autonumberdigits"] = 1;

  // If you have a custom module that implements eventscodes, configure it's name here
  // Example: $config["eventscode_module"] = "mymodule";
  $config["eventscode_module"] = "";
  
  // Use autocomplete field instead of a events dropdown
  $config['events_selection_autocomplete']=false;
  
  // The number of recents eventss we show in the dropdown
  $config['numberofrecenteventss']=10;
  
  // When contacts needs to be obligatory, set this option to true
  $config['events_contact_obligatory']=false;
  
  // The following configs are for copying a skel events directory
  // to a new location.
  
  // Project skel directory
  $config['events_dir_skel']='';
  
  // Project destination directory
  $config['events_dir_destination']='';

  // Project directory template, here you can use attributes from the
  // events node. 
  // Example: $config['events_dir_name_template']='[id]_[abbreviation]';
  $config['events_dir_name_template']='';
  
  // Project mail format, valid values are 'html' and 'htmlplain'
  $config['events_formatmail']='html';
  
  // Send of the events dir creation mail
  $config['mail_sender']='';
  
  // Receiver of the events dir creation mail
  $config['events_sendto']='';
  

?>
