<?php
 /**
  * This file is part of the Achievo distribution.
  * Detailed copyright and licensing information can be found
  * in the doc/COPYRIGHT and doc/LICENSE files which should be
  * included in the distribution.
  * eventstpl_doctype node class file
  *
  * @package achievo
  * @subpackage docmanager
  *
  * @copyright (c)2008 Ibuildings B.V.
  * @license http://www.achievo.org/licensing Achievo Open Source License
  *
  * @version $Revision: 5078 $
  * $Id: class.eventstpl_doctype.inc 5078 2008-06-30 21:22:57Z sandy $
  */

  /**
   * @internal includes
   */
  userelation("atkmanytoonerelation");

 /**
  * The node class for eventstpl_doctype.
  *
  * @author ivo <ivo@ibuildings.nl>
  * @author guido <guido@ibuildings.nl>
  * @package achievo_modules
  * @subpackage docmanager
  */
 class eventstpl_doctype extends atkNode
 {
   /**
    * eventstpl_doctype constructor
    */
   function eventstpl_doctype()
   {
     // Call the base class constructor
     $this->atkNode("eventstpl_doctype");

     // Add the relations to both the tpl_events and the documenttype tables
     $this->add(new atkManyToOneRelation("eventstpl_id", "events.tpl_events", AF_PRIMARY));
     $this->add(new atkManyToOneRelation("documenttype_id", "docmanager.documenttype", AF_PRIMARY));

     // Set the table for this node
     $this->setTable("docmanager_prjtpl_dt");
   }

 }

?>