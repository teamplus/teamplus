<?php

class events_category extends atkNode
{
  function events_category()
  {
    $this->atkNode("events_category");

    $this->add(new atkAttribute("id",AF_AUTOKEY));
    $this->add(new atkAttribute("events_category",AF_OBLIGATORY|AF_UNIQUE|AF_SEARCHABLE, 50));

    $this->setTable("events_category");
    $this->setOrder("events_category");
    $this->setDescriptorTemplate("[events_category]");
    $this->setSecurityAlias("events.activity");
  }

}
?>