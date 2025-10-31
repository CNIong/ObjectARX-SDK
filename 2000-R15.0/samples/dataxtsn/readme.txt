
    To store data on an existing object,  there are two common mechanisms to
    use:

      - Using Protocol Extension to attach/manipulate Xdata on the object for
        which the data is needed.

      - Defining an AcDbObject class to be stored in the extension dictionary
        of the object for which the data is needed.

    Both of these methodes are logically eqivalent operations, however they
    have different qualities and capacities,  which need to be compared to
    the needs of the problem at hand.

    The basic difference is that protocol extension/xdata has less storage
    overhead, but a limited capacity (i.e. Xdata has a 16k per object limit),
    while extension dictionaries have essentially unlimited storage capacity,
    but more storage overhead.

    In the two sample programs provided in this directory, we are using the
    mechanisms to effectively add a string variable to any instance of
    AcDbObject.  In this trivial endeavor,  the protocol extension + xdata
    version -specific code is roughly 260 lines versus about 200 lines for
    the extension dictionary version,  including comments. So, both mechanisms
    are the same general order of magnitude in coding.  The protocol extension
    + xdata form is considerably more compact in storage overhead.  But imagine
    a version where either 200K per object was required, or over a hundred
    distinct heterogenous fields were needed.  That custom object,  with
    compiled-in random access to all those fields wouldn't look nearly as bad
    as the corresponding resbuf chain parser for Xdata, now would it?

    Key points:

    - The amount of XData per AcDbObject instance is restricted to a total of
      16K bytes for all REGAPP groups. 

    - The amount of overhead for Xdata is roughly 12 bytes per object plus
      another 12 bytes per REGAPP group.  The amount of overhead for an
      object in the dictionary is roughly 60 bytes for the extension
      dictionary itself, plus another 60 bytes for the object in the
      dictionary, plus the length of the lookup string.

    - The extension dictionary AND the entry object in question must be
      opened and closed when they are used, Xdata is part of the main object.

    - The extension dictionary objects can be persistent reactors,  and
      recieve notification whenever anything happens to their master object
      (most easily read as their owner's owner).  Protocol Extension, with
      or without Xdata, can't do this.  Wow, now that's worth a few extra
      bytes, isn't it?

    - Xdata is preserved in both DXF and DWG, and R12 DWG saves,  regardless
      of whether the application is present.  Custom data objects (other than
      Xrecords) will become proxies when the app is not present to support them.
      Proxy (zombie in R13) objects are not written to either R12 DWG files,
      nor pre-R13c4 DXF files.

    - Conversely, there is no way for Xdata-based extensions to find out that
      the database went through edits when the DRAWING was loaded without the
      ARX app being present.
    
