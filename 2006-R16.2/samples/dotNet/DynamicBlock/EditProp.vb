' Copyright (C) 2004 by Autodesk, Inc.

'Permission to use, copy, modify, and distribute this software in
'object code form for any purpose and without fee is hereby granted, 
'provided that the above copyright notice appears in all copies and 
'that both that copyright notice and the limited warranty and
'restricted rights notice below appear in all supporting 
'documentation.

'AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
'AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
'MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
'DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
'UNINTERRUPTED OR ERROR FREE.

'Use, duplication, or disclosure by the U.S. Government is subject to 
'restrictions set forth in FAR 52.227-19 (Commercial Computer
'Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
'(Rights in Technical Data and Computer Software), as applicable.

Imports System
Imports System.Drawing
Imports System.Collections
Imports System.ComponentModel
Imports System.Windows.Forms
Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.ApplicationServices
Imports Autodesk.AutoCAD.DatabaseServices

Namespace DynamicBlock.Forms
    Public Class EditPropForm
        Inherits System.Windows.Forms.Form

        Dim m_dynBlkUtil As DynBlockUtil
        Dim m_blockId As ObjectId

        ' Connect to the objectId of the block reference
        Public Sub SetBlockId(ByVal blkId As ObjectId)
            If Not blkId.IsNull Then
                m_blockId = blkId
                PopulateGrid()
            Else
                MessageBox.Show("EditProp.vb Form: cannot set null objectId")
            End If
        End Sub

        Private Sub PopulateGrid()
            'You should call this function only after you set the objectId of the block -
            ' - using SetBlockId
            m_dynBlkUtil = New DynBlockUtil(m_blockId)

            'Data grid to show block ref properties
            Dim propArray As ArrayList
            m_dynBlkUtil.GetProps(propArray)

            ' map the grid data to the property array list
            m_DataGrid.DataSource = propArray

            'Create a table style 
            Dim tableStyle As DataGridTableStyle = New DataGridTableStyle()
            tableStyle.MappingName = "ArrayList"

            'Create a colum for property name
            Dim dgTextBoxName As DataGridTextBoxColumn = New DataGridTextBoxColumn()
            dgTextBoxName.MappingName = "PropertyName"
            dgTextBoxName.HeaderText = "Name"
            dgTextBoxName.Format = "g"
            dgTextBoxName.ReadOnly = True
            tableStyle.GridColumnStyles.Add(dgTextBoxName)

            'Create a colum for property type
            Dim dgTextBoxType As DataGridTextBoxColumn = New DataGridTextBoxColumn()
            dgTextBoxType.MappingName = "PropertyType"
            dgTextBoxType.HeaderText = "Type"
            dgTextBoxType.Format = "g"
            dgTextBoxType.ReadOnly = True
            tableStyle.GridColumnStyles.Add(dgTextBoxType)

            'Create a colum for property Val
            Dim dgTextBoxVal As DataGridTextBoxColumn = New DataGridTextBoxColumn()
            dgTextBoxVal.MappingName = "Value"
            dgTextBoxVal.HeaderText = "Value"
            dgTextBoxVal.Format = "g"
            dgTextBoxVal.ReadOnly = False
            tableStyle.GridColumnStyles.Add(dgTextBoxVal)

            'Create a colum for property description
            Dim dgTextBoxDesc As DataGridTextBoxColumn = New DataGridTextBoxColumn()
            dgTextBoxDesc.MappingName = "Description"
            dgTextBoxDesc.HeaderText = "Description"
            dgTextBoxDesc.Format = "g"
            dgTextBoxDesc.ReadOnly = True
            dgTextBoxDesc.Width = 200
            tableStyle.GridColumnStyles.Add(dgTextBoxDesc)

            m_DataGrid.TableStyles.Clear()
            m_DataGrid.TableStyles.Add(tableStyle)
            '''''''''''''''''''''''''''''''''''''''''''''''''''
        End Sub

      
#Region " Windows Form Designer generated code "

        Public Sub New()
            MyBase.New()

            'This call is required by the Windows Form Designer.
            InitializeComponent()

            'Add any initialization after the InitializeComponent() call
            m_blockId = New ObjectId()
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
        Friend WithEvents m_bnOk As System.Windows.Forms.Button
        Friend WithEvents m_Label As System.Windows.Forms.Label
        Friend WithEvents m_DataGrid As System.Windows.Forms.DataGrid
        <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
            Me.m_bnOk = New System.Windows.Forms.Button()
            Me.m_Label = New System.Windows.Forms.Label()
            Me.m_DataGrid = New System.Windows.Forms.DataGrid()
            CType(Me.m_DataGrid, System.ComponentModel.ISupportInitialize).BeginInit()
            Me.SuspendLayout()
            '
            'm_bnOk
            '
            Me.m_bnOk.DialogResult = System.Windows.Forms.DialogResult.Cancel
            Me.m_bnOk.Location = New System.Drawing.Point(168, 248)
            Me.m_bnOk.Name = "m_bnOk"
            Me.m_bnOk.Size = New System.Drawing.Size(56, 24)
            Me.m_bnOk.TabIndex = 2
            Me.m_bnOk.Text = "OK"
            '
            'm_Label
            '
            Me.m_Label.Location = New System.Drawing.Point(24, 8)
            Me.m_Label.Name = "m_Label"
            Me.m_Label.Size = New System.Drawing.Size(72, 16)
            Me.m_Label.TabIndex = 5
            Me.m_Label.Text = "Properties"
            '
            'm_DataGrid
            '
            Me.m_DataGrid.DataMember = ""
            Me.m_DataGrid.GridLineStyle = System.Windows.Forms.DataGridLineStyle.None
            Me.m_DataGrid.HeaderForeColor = System.Drawing.SystemColors.ControlText
            Me.m_DataGrid.Location = New System.Drawing.Point(16, 32)
            Me.m_DataGrid.Name = "m_DataGrid"
            Me.m_DataGrid.RowHeadersVisible = False
            Me.m_DataGrid.Size = New System.Drawing.Size(360, 208)
            Me.m_DataGrid.TabIndex = 6
            '
            'EditPropForm
            '
            Me.AcceptButton = Me.m_bnOk
            Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
            Me.AutoScroll = True
            Me.CancelButton = Me.m_bnOk
            Me.ClientSize = New System.Drawing.Size(390, 276)
            Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.m_DataGrid, Me.m_Label, Me.m_bnOk})
            Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D
            Me.MaximizeBox = False
            Me.Name = "EditPropForm"
            Me.Text = "Edit Dynamic Block Reference"
            CType(Me.m_DataGrid, System.ComponentModel.ISupportInitialize).EndInit()
            Me.ResumeLayout(False)

        End Sub

#End Region


    End Class
End Namespace