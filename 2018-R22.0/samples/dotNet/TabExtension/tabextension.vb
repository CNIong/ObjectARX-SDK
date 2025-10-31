' Copyright 2017 Autodesk, Inc.  All rights reserved.

' Use of this software is subject to the terms of the Autodesk license 
' agreement provided at the time of installation or download, or which  
' otherwise accompanies this software in either electronic or hard copy form.   

Imports Autodesk.AutoCAD.Runtime

<Assembly: CommandClass(GetType(TabExtension))> 

Public Class TabExtension
    Inherits System.Windows.Forms.UserControl

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'UserControl overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents Label1 As System.Windows.Forms.Label
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.Anchor = (((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
                    Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right)
        Me.Label1.Location = New System.Drawing.Point(32, 112)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(184, 23)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "This Page Intentionally Left Blank."
        '
        'TabExtension
        '
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.Label1})
        Me.Name = "TabExtension"
        Me.Size = New System.Drawing.Size(248, 248)
        Me.ResumeLayout(False)

    End Sub

#End Region
    Public Sub OnOk()
        System.Windows.Forms.MessageBox.Show("OnOk")
    End Sub
    Public Sub OnCancel()
        System.Windows.Forms.MessageBox.Show("OnCancel")
    End Sub
    Public Sub OnHelp()
        System.Windows.Forms.MessageBox.Show("OnHelp")
    End Sub
    <Autodesk.AutoCAD.Runtime.CommandMethod("tabdemo")> _
    Public Shared Sub DoIt()
        AddHandler Autodesk.AutoCAD.ApplicationServices.Application.DisplayingOptionDialog, AddressOf Application_TabbedDialog
        AddHandler Autodesk.AutoCAD.ApplicationServices.Application.DisplayingDraftingSettingsDialog, AddressOf Application_TabbedDialog
        AddHandler Autodesk.AutoCAD.ApplicationServices.Application.DisplayingCustomizeDialog, AddressOf Application_TabbedDialog
    End Sub
    Private Shared Sub Application_TabbedDialog(ByVal sender As Object, ByVal e As Autodesk.AutoCAD.ApplicationServices.TabbedDialogEventArgs)
        Dim ctrl As TabExtension = New TabExtension()
        e.AddTab(".NET Demo", _
            New Autodesk.AutoCAD.ApplicationServices.TabbedDialogExtension( _
            ctrl, _
            New Autodesk.AutoCAD.ApplicationServices.TabbedDialogAction(AddressOf ctrl.OnOk), _
            New Autodesk.AutoCAD.ApplicationServices.TabbedDialogAction(AddressOf ctrl.OnCancel), _
            New Autodesk.AutoCAD.ApplicationServices.TabbedDialogAction(AddressOf ctrl.OnHelp) _
            ) _
            )
    End Sub

End Class

