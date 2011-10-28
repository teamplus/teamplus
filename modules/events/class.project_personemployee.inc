<?php

/**
 * Module Project
 * Class events_personemployee
 *
 * This class makes it possible to relate employees to a events in a certain role(s).
 *
 * $Id: class.events_personemployee.inc 1800 2006-07-31 13:01:10Z guido $
 * @author L. Willems  <lineke@ibuildings.nl>
 * @version $Revision: 1800 $
 *
 */

userelation("atkmanytoonerelation");

class events_personemployee extends atkNode
{
  function events_personemployee()
  {
    $this->atkNode("events_personemployee");

    $this->add(new atkManyToOneRelation("eventsid", "events.events", AF_OBLIGATORY|AF_PRIMARY|AF_HIDE));
    $this->add(new atkManyToOneRelation("personid", "employee.employee", AF_OBLIGATORY|AF_PRIMARY|AF_RELATION_AUTOLINK));
    $this->add(new atkManyToOneRelation("role", "events.role", AF_PRIMARY|AF_RELATION_AUTOLINK));
    $this->addFilter("personid.role = 'employee'");

    // If you may edit the events, you may also add contactpersons to it.
    $this->setSecurityAlias("events.events");
    foreach(array("add", "save", "update", "delete") as $action)
      $this->m_securityMap[$action] = "edit";

    $this->setTable("events_person", "events_person");
  }

  function action_delete(&$handler)
  {
    // When deleting, the above filter won't work. But that doesn't matter, we
    // don't need it anyway.
    $this->m_flags |= NF_NO_FILTER;
    return $handler->action_delete();
  }

}

?>