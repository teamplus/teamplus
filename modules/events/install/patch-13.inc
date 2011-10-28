<?php

  $setup->alterColumn("events", "enddate", "enddate", "date", true);
  $setup->alterColumn("events", "startdate", "startdate", "date", true);

  $db->query("UPDATE events SET startdate = NULL WHERE startdate = '0000-00-00'");
  $db->query("UPDATE events SET enddate = NULL WHERE enddate = '0000-00-00'");
  
?>
