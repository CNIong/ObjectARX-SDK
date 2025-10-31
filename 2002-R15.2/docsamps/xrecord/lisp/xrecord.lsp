;;;    Copyright (C) 1996,1998 by Autodesk, Inc.
;;;
;;;    Permission to use, copy, modify, and distribute this software
;;;    for any purpose and without fee is hereby granted, provided
;;;    that the above copyright notice appears in all copies and
;;;    that both that copyright notice and the limited warranty and
;;;    restricted rights notice below appear in all supporting
;;;    documentation.
;;;
;;;    AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
;;;    AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
;;;    MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
;;;    DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
;;;    UNINTERRUPTED OR ERROR FREE.
;;;
;;;    Use, duplication, or disclosure by the U.S. Government is subject to
;;;    restrictions set forth in FAR 52.227-19 (Commercial Computer
;;;    Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) 
;;;    (Rights in Technical Data and Computer Software), as applicable.
;;;

(defun c:asdk_lisp_create (/ xrec xname dict dname)
    ; create the Xrecord entity's data list
    (setq xrec '((0 . "XRECORD")(100 . "AcDbXrecord")
                (1 . "This is a test Xrecord list")
                (10 1.0 2.0 0.0) (40 . 3.14159) (50 . 3.14159)
                (62 . 1) (70 . 180))
    )

    ; use entmakex to create the Xrecord with no owner
    (setq xname (entmakex xrec))

    ; Within the named object dictionary,  attempt to get the
    ; entity name of the dictionary associated with the key
    ; "ASDK_DICT".  If it doesn't exist,  create it.
    (setq dname (cdr (assoc -1 (dictsearch (namedobjdict) "ASDK_DICT"))))
    (if (not dname) (progn
        (setq dict '((0 . "DICTIONARY")(100 . "AcDbDictionary")))
        (setq dname (entmakex dict))
        (dictadd (namedobjdict) "ASDK_DICT" dname))
    )
    ; add the new Xrecord entity to the named object dictionary
    (dictadd dname "XRECLISP" xname)

    (princ)
)


(defun c:asdk_lisp_listxrec (/ xlist dname)
    ; find the dictionary associated with the key "ASDK_DICT"
    (setq dname (cdr (assoc -1 (dictsearch (namedobjdict) "ASDK_DICT"))))
 
    ; find the Xrecord in the ASDK_DICT dictionary
    (setq xlist (dictsearch dname "XRECLISP"))

    ; print out the Xrecord's data list
    (princ xlist)

    (princ)
)
