<?php

  userelation("atkmanytoonerelation");
  
  class dependency extends atkNode
  {
    function dependency()
    {
      // Dummy readonly class for accessing dependency information.
      // For editing dependencies, use the dependency attribute.
      $this->atkNode("dependency", NF_READONLY);
      
      $this->add(new atkManyToOneRelation("phaseid_row", "events.phase", AF_PRIMARY));
      $this->add(new atkManyToOneRelation("phaseid_col", "events.phase", AF_PRIMARY));

      $this->setTable("dependency");
    }
  }
?>