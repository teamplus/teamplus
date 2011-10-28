<?php

/**
 * Module Project
 * Class events_personcontact
 *
 * This class makes it possible to relate contacts to a events in a certain role(s).
 *
 * $Id: class.events_personcontact.inc 2106 2007-03-19 22:17:16Z sandy $
 * @author L. Willems  <lineke@ibuildings.nl>
 * @version $Revision: 2106 $
 *
 */

userelation("atkmanytoonerelation");
useattrib("docmanager.relateddocument");

class events_personcontact extends atkNode
{
  function events_personcontact()
  {
    $this->atkNode("events_personcontact");

    $this->add(new atkManyToOneRelation("eventsid", "events.events", AF_OBLIGATORY|AF_PRIMARY|AF_HIDE));
    $this->add(new atkManyToOneRelation("personid", "events.select_contact", AF_OBLIGATORY|AF_PRIMARY|AF_RELATION_AUTOLINK|AF_LARGE));
    $this->add(new atkManyToOneRelation("role", "events.role", AF_OBLIGATORY|AF_PRIMARY|AF_RELATION_AUTOLINK));
    $this->add(new relatedDocument("document", "eventsid"));


    $this->addFilter("personid.role = 'contact'");

    // If you may edit the events, you may also add contactpersons to it.
    $this->setSecurityAlias("events.events");
    foreach(array("add", "save", "update", "delete") as $action)
      $this->m_securityMap[$action] = "edit";

    $this->setTable("events_person", "events_person");
    $this->setOrder("eventsid.name ASC, personid.lastname ASC");
    $this->setDescriptorTemplate("[eventsid.name] ([personid.lastname], [personid.firstname])");
  }

  function action_delete(&$handler)
  {
    // When deleting, the above filter won't work. But that doesn't matter, we
    // don't need it anyway.
    $this->m_flags |= NF_NO_FILTER;
    return $handler->action_delete();
  }

  function assignDocumentVars(&$documentWriter, $selector)
  {
    // Load the selected record from the database
    $events_personcontactrecord = $this->selectDb($selector);
    $documentWriter->assignDocumentSingleRecord($this, $events_personcontactrecord[0]);

    // Assign the referenced events
    $eventsnode = &atkGetNode("events.events");
    $eventsrecord = $eventsnode->selectDb("events.id='".$events_personcontactrecord[0]["eventsid"]["id"]."'");
    $documentWriter->assignDocumentSingleRecord($eventsnode, $eventsrecord[0], "events_", "", "", "", "", "view");

    // Assign the referenced personcontact
    $personcontactnode = &atkGetNode("events.select_contact");
    $personcontactrecord = $personcontactnode->selectDb("person.id='".$events_personcontactrecord[0]["personid"]["id"]."'");
    $documentWriter->assignDocumentSingleRecord($personcontactnode, $personcontactrecord[0], "person_", "", "", "", "", "view");

    // Assign the referenced personcontact's organization (if available)
    $organizationnode = &atkGetNode("organization.organization");
    $organizationrecord = $organizationnode->selectDb("organization.id='".$personcontactrecord[0]["company"]["id"]."'", "", "", "", "", "view");
    if (count($organizationrecord) > 0)
    {
      $documentWriter->assignDocumentSingleRecord($organizationnode, $organizationrecord[0], "organization_");
    }

    // Use an evil global to let the tbsooo engine use the precence of an organization
    global $documentvar_organizationpresent;
    $documentvar_organizationpresent = (count($organizationrecord) > 0) ? 1 : 0;

    // Assign the referenced coordinator
    $employeenode = &atkGetNode("employee.employee");
    $coordinatorrecord = $employeenode->selectDb("person.id='".$eventsrecord[0]["coordinator"]["id"]."'", "", "", "", "", "view");
    $documentWriter->assignDocumentSingleRecord($employeenode, $coordinatorrecord[0], "coordinator_");

    // Also assign the generic (date) vars tot the documentWriter
    $documentWriter->assignDocumentGenericVars();
  }
}

?>