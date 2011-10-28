<?php

userelation("atkmanytoonerelation");

class tpl_events_phase extends atkNode
{
  function tpl_events_phase()
  {
    $this->atkNode("tpl_events_phase",NF_NO_EDIT); // node() constructor is *not* called automatically!

    $this->addAllowedAction(array("add","delete","edit","view"));

    $this->add(new atkManyToOneRelation("eventsid","events.tpl_events",AF_PRIMARY|AF_HIDE_LIST));
    $this->add(new atkManyToOneRelation("phaseid","events.tpl_phase",AF_PRIMARY));

    $this->setTable("tpl_events_phase");
  }

  function descriptor_def()
  {
    return "[phaseid.name]";
  }

  function postDel($rec)
  {
    // delete dependencies..
    $db = &atkGetDb();
    $delquery = "DELETE FROM
                 tpl_dependency
               WHERE
                 eventsid = ".$rec["eventsid"]["id"]."
                 AND (phaseid_row = ".$rec["phaseid"]["id"]." OR phaseid_col = ".$rec["phaseid"]["id"].")";

    $db->query($delquery);
    return true;
  }
}
?>