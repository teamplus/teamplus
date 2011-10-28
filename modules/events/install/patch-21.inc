<?php

  // Make the events name column larger
  $setup->alterColumn("events", "name", "name", "VARCHAR(200)", false);

?>
