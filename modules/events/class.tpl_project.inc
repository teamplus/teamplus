<?php

useattrib("events.tpl_dependencyattrib");
useattrib("atktextattribute");
useattrib("atknumberattribute");
userelation("atkonetomanyrelation");
userelation("atkmanyboolrelation");

class tpl_events extends atkNode
{
  function tpl_events()
  {
    $this->atkNode("tpl_events",NF_EDITAFTERADD);

    $this->add(new atkNumberAttribute("id",AF_AUTOKEY));
    $this->add(new atkAttribute("name",AF_UNIQUE|AF_SEARCHABLE|AF_OBLIGATORY, 50));
    $this->add(new atkTextAttribute("description",TEXT_LARGE, AF_HIDE_ADD));
    $this->add(new atkOneToManyRelation("tpl_events_phase","events.tpl_events_phase","eventsid", AF_HIDE_ADD|AF_HIDE_LIST|AF_NOSORT));
    $this->add(new tpl_dependencyAttribute("dependencies",AF_HIDE_ADD|AF_HIDE_LIST|AF_BLANKLABEL));
    $rel = &$this->add(new atkManyBoolRelation("documenttypes", "docmanager.eventstpl_doctype", "docmanager.documenttype", AF_HIDE_LIST|AF_HIDE_ADD));
    $rel->setLocalKey("eventstpl_id");
    $rel->setRemoteKey("documenttype_id");
    $rel->setDestinationFilter("master='events.events'");

    $this->setTable("tpl_events","tpl_events");
    $this->setOrder("name");
  }

  function descriptor_def()
  {
    return "[name]";
  }

  function initial_values()
  {
    return array("status"=>"active");
  }
}
?>
