' Copyright 2017 Autodesk, Inc.  All rights reserved.

' Use of this software is subject to the terms of the Autodesk license 
' agreement provided at the time of installation or download, or which  
' otherwise accompanies this software in either electronic or hard copy form.   

' Hello World VB.NET sample
' by Cyrille Fauvel - Autodesk Developer Technical Services
Option Explicit On 

Imports System
Imports System.Type
Imports System.Windows.Forms

Namespace HelloWorld

    Public Class HellowWorldForm
        Inherits System.Windows.Forms.Form

#Region " Windows Form Designer generated code "

        Public Sub New()
            MyBase.New()

            'This call is required by the Windows Form Designer.
            InitializeComponent()

            'Add any initialization after the InitializeComponent() call

        End Sub

        'Form overrides dispose to clean up the component list.
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
        Friend WithEvents OkButton As System.Windows.Forms.Button
        <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
            Me.Label1 = New System.Windows.Forms.Label()
            Me.OkButton = New System.Windows.Forms.Button()
            Me.SuspendLayout()
            '
            'Label1
            '
            Me.Label1.Location = New System.Drawing.Point(16, 16)
            Me.Label1.Name = "Label1"
            Me.Label1.Size = New System.Drawing.Size(296, 23)
            Me.Label1.TabIndex = 0
            Me.Label1.Text = "Hello World! VB .NET sample application"
            '
            'OkButton
            '
            Me.OkButton.CausesValidation = False
            Me.OkButton.DialogResult = System.Windows.Forms.DialogResult.OK
            Me.OkButton.Location = New System.Drawing.Point(168, 56)
            Me.OkButton.Name = "OkButton"
            Me.OkButton.TabIndex = 1
            Me.OkButton.Text = "Ok"
            '
            'Form1
            '
            Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
            Me.ClientSize = New System.Drawing.Size(408, 86)
            Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.OkButton, Me.Label1})
            Me.Name = "Form1"
            Me.Text = "Hello World!"
            Me.ResumeLayout(False)

        End Sub

#End Region

    End Class

End Namespace