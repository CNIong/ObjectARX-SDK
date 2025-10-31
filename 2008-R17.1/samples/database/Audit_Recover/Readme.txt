// (C) Copyright 2002-2006 by Autodesk, Inc. 
//

Audit_Recover ObjectARX SDK Sample

The Audit_Recover sample demonstrates how a custom entity can subscribe to a drawing recovery operation in AutoCAD, and participate in object recreation and recovery for the entities described with custom modules.

The sample demonstrates a custom entity (AsdkEntity) and a custom style (AsdkStyle) which are referenced to each other via hard pointer.  The sample also demonstrates the AcDbAuditRecreatePE protocol extension derivitive class (AsdkStyleRecreator).  This class is attached to the AsdkStyle class and demonstrates how drawing corruption can be fixed with the use of this class.


the AcDbAuditRecreatePE Protocol extension class:

The AcDbAuditRecreatePE class defines the runtime extension protocol for audit-time object recreation.  the contract is very simple.  All 3 member functions (replace, redirect and fetchObject) are invoked in the context of RECOVER.  The contract is:  When an object of a given class is requested via AcDbAuditInfo::fetchObject, and is not valid, then first the PI objec's replace() member is invoked.  If it returns eOk and a new instance of the class then that instance is placed in the original objectId, and the repair is finished.  If however it fails then the PE object's redirect() member is invoked.  If that returns true, then the new objectID is used for that object from then on.  If redirect() returns false, then the object reference is no longer valid and "NULL" is returned for a new objectID.  Instance of this class will be invoked from the Audit complex when an instance of a given class is to be "recreated" because an original one is missing.

To test the sample:

Build and load the AsdkAudit_Recover.arx module into AutoCAD.  The sample defines the following commands:

	CREATE (prompts user to pick a point) – creates an instance of a custom entity (“AsdkEntity”) in Model Space along with a hard 	pointer to a style (“AsdkStyle”) placed in the NOD. 
 

	CORRUPT will set the hard pointer in AsdkEntity to point to the block table, thereby corrupting the AsdkEntity.
 

	CORRUPT2 will set the hard pointer to NULL, and erase the AsdkStyle altogether, corrupting the entity and erasing the style.
 

	GETSTYLE will list the style that is connected to the entity - simply verifying the simple link.
 
The recover functionality will be invoked during a RECOVER command.  Therefore run CREATE, then either CORRUPT or CORRUPT2, then save the drawing and run RECOVER on it.  The custom entities should be prepared to recover from these scenarios.



