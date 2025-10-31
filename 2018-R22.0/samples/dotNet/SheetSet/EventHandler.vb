' Copyright 2017 Autodesk, Inc.  All rights reserved.

' Use of this software is subject to the terms of the Autodesk license 
' agreement provided at the time of installation or download, or which  
' otherwise accompanies this software in either electronic or hard copy form.   

Option Explicit On
Imports ACSMCOMPONENTS22Lib

Public Class EventHandler
    Implements IAcSmEvents

    Private Sub IAcSmEvents_OnChanged(ByVal ev As AcSmEvent, ByVal comp As IAcSmPersist) Implements IAcSmEvents.OnChanged
        Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor.WriteMessage(comp.GetTypeName & "  Modified!!!  " & vbCrLf)
    End Sub

End Class
