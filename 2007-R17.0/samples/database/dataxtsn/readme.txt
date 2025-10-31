DATAXTSN sample Readme.txt

 (C) Copyright 2001-2006 by Autodesk, Inc.

    To store data on an existing object,  there are two common mechanisms in
    use:

     1 - Use Protocol Extension to attach/manipulate Xdata on the object for
         which the data is needed.

     2 - Define an AcDbObject class to be stored in the extension dictionary
         of the object for which the data is needed.

    These methods are logically equivalent operations, but they have different
    qualities and capacities, which need to be compared to the requirements of
    the problem.

    The basic difference is that Protocol Extension Xdata has less storage
    overhead, but a limited capacity (i.e. Xdata has a 16k per object limit),
    while Extension Dictionaries have essentially unlimited storage capacity
    but more storage overhead.

    In the two sample programs provided in this directory, we are using the
    mechanisms to effectively add a string variable to any instance of
    AcDbObject.  In this trivial endeavor,  the Protocol Extension Xdata
    version, the specific code is roughly 260 lines versus about 200 lines for
    the Extension Dictionary version,  including comments. So, both mechanisms
    require the same amount of code.  The Protocol Extension Xdata form is
    considerably more compact in storage overhead.  But imagine
    a version where either 200K per object was required, or over a hundred
    distinct heterogenous fields were needed.  That custom object,  with
    compiled-in random access to all those fields wouldn't look nearly as bad
    as the corresponding resbuf chain parser for Xdata.


    There are two commands defined in Edinvent:

    GET_ID
      will ask the user to select an object,  then print the last known
      inventory Id, or else print a message stating that the object doesn't
      have an Id yet.

    SET_ID
      will prompt for an object first, then a string to be attached to it as
      the Inventory Id.

    For either command, you can either pick an entity, or type "H" at the
    pick prompt, then enter in the hexadecimal representation of any object
    handle (remember, entities are objects too!).


    There are two commands defined in Peinvent:

    GETID
      will ask the user to select an object,  then print the last known
      inventory Id, or else print a message stating that the object doesn't
      have an Id yet.

    SETID
      will prompt for an object first, then a string to be attached to it as
      the Inventory Id.

    For either command, you can either pick an entity, or type "H" at the
    pick prompt, then enter in the hexadecimal representation of any object
    handle (remember, entities are objects too!).


    Key points:

    1 - The amount of XData per AcDbObject instance is restricted to a total of
        16K bytes for all REGAPP groups. 

    2 - The amount of overhead for Xdata is roughly 12 bytes per object plus
        another 12 bytes per REGAPP group.  The amount of overhead for an
        object in the dictionary is roughly 60 bytes for the extension
        dictionary itself, plus another 60 bytes for the object in the
        dictionary, plus the length of the lookup string.

    3 - The Extension Dictionary and the entry object in question must be
        opened and closed when they are used whereas Xdata is part of the
        main object.

    4 - The Extension Dictionary objects can be persistent reactors, and
        recieve notification whenever anything happens to their master object
        (most easily read as their owner's owner).  Protocol Extension, with
        or without Xdata, can't do this.

    5 - Xdata is preserved in both DXF and DWG formats, and Release 12 DWG formats
        regardless of whether the application is present. Custom data objects (other
        than Xrecords) will become proxies when the application is not present to
        support them. Proxy (zombie in R13) objects are not written to either Release
        12 DWG files, nor pre-Release 13c4 DXF files.

    6 - Conversely, there is no way for Xdata-based extensions to find out that
        the database went through edits when the drawing was loaded without the
        ARX app being present.
    
