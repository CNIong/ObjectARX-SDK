//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2017 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


using System;
using System.Collections;
using System.Reflection;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.Geometry;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.ApplicationServices;

[assembly: ExtensionApplication(null)]
[assembly: CommandClass(typeof(filer.TestFiler))]

namespace filer
{

    public class TestFiler
    {
        ///Defines a command which prompt a message on the AutoCAD command line
        [CommandMethod("runfiler")]
        public void filer()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            PromptEntityOptions opt = new PromptEntityOptions("Select an object to dump");
            PromptEntityResult res ;
            do
            {
                res = ed.GetEntity(opt);
                opt.Message = "\nNo object selected. Select an object to dump";
            }
            while (res.Status == PromptStatus.Error);
            if (res.Status == PromptStatus.OK)
            {
                using (Transaction t = Application.DocumentManager.MdiActiveDocument.Database.TransactionManager.StartTransaction())
                {
                    Entity ent = (Entity)t.GetObject(res.ObjectId,OpenMode.ForRead);
                    MyFiler filer = new MyFiler();
                    ent.DwgOut(filer);
                    t.Commit();
                }
            } 
        }
    }


    class MyFiler : Autodesk.AutoCAD.DatabaseServices.DwgFiler
    {
        string fileType = "";
        string dwgVersion = "";
        public MyFiler()
        {
        }

        ///  _____________________  Data Reading    _____________________
    
        public override System.IntPtr ReadAddress()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return new System.IntPtr ();
        }

        public override byte[] ReadBinaryChunk()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return null;
        }

        public override bool ReadBoolean()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return false;
        }

        public override byte ReadByte()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return 0;
        }

        public override void ReadBytes(byte[] value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
        }

        public override double ReadDouble()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return 0;
        }

        public override Handle ReadHandle()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return new Handle ();
        }

        public override ObjectId ReadHardOwnershipId()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return new ObjectId ();
        }

        public override ObjectId ReadHardPointerId()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return new ObjectId ();
        }

        public override short ReadInt16()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return 0;
        }

        public override int ReadInt32()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return 0;
        }

        public override Int64 ReadInt64()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return 0;
        }

        public override Point2d ReadPoint2d()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return new Point2d();
        }

        public override Point3d ReadPoint3d()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return new Point3d();
        }

        public override Scale3d ReadScale3d()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return new Scale3d();
        }

        public override ObjectId ReadSoftOwnershipId()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return new ObjectId ();
        }

        public override ObjectId ReadSoftPointerId()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return new ObjectId ();
        }

        public override string ReadString()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return null;
        }

        public override ushort ReadUInt16()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return 0;
        }

        public override uint ReadUInt32()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return 0;
        }

        public override UInt64 ReadUInt64()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return 0;
        }

        public override Vector2d ReadVector2d()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return new Vector2d();
        }

        public override Vector3d ReadVector3d()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            return new Vector3d();
        }

        public override void ResetFilerStatus()
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
        }

        public override void Seek(Int64 offset, int method)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
        }

        ///  _____________________  Data Writing    _____________________
        
        public override void WriteAddress(System.IntPtr value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
            ed.WriteMessage(value.ToString()+"\n");

        }

        public override void WriteBinaryChunk(byte[] chunk)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
        }

        public override void WriteBoolean(bool value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");

        }

        public override void WriteByte(byte value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override void WriteBytes(byte[] value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");

        }

        public override void WriteDouble(double value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override void WriteHandle(Handle handle)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
        }

        public override void WriteHardOwnershipId(ObjectId value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override void WriteHardPointerId(ObjectId value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override void WriteInt16(short value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");

        }

        public override void WriteInt32(int value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override void WriteInt64(Int64 value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString() + "\n");
        }

        public override void WritePoint2d(Point2d value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override void WriteScale3d(Scale3d value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override void WriteSoftOwnershipId(ObjectId value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override void WriteSoftPointerId(ObjectId value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override void WriteString(string value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override void WriteUInt16(ushort value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override void WriteUInt32(uint value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override void WriteUInt64(UInt64 value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString() + "\n");
        }

        public override void WriteVector2d(Vector2d value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override void WriteVector3d(Vector3d value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+"\n");
        }

        public override FullDwgVersion DwgVersion
        {
            get
            {
                Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
                if (dwgVersion != base.DwgVersion.ToString())
                {
                    dwgVersion = base.DwgVersion.ToString();
                    ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + dwgVersion +"\n");
                }
                return base.DwgVersion;
            }
        }
        
        public override ErrorStatus FilerStatus
        {
            get
            {
                Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
                // ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + FilerStatus.GetType() + "\n");
                return new ErrorStatus ();
            }
            set
            {
                Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
                ed.WriteMessage(MethodInfo.GetCurrentMethod().Name +  " = " + "\n");
            }
        }

        public override FilerType FilerType
        {
            get
            {
                Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
                if (fileType != FilerType.CopyFiler.ToString())
                {
                    fileType = FilerType.CopyFiler.ToString();
                    ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + fileType +" \n");
                }
                return FilerType.CopyFiler;
            }
            
        }

        public override Int64 Position
        {
            get
            {
                Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
                ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = " + "\n");
                return 0;
            }
        }

        public override void WritePoint3d(Point3d value)
        {
            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;  
            ed.WriteMessage(MethodInfo.GetCurrentMethod().Name + " = ");
            ed.WriteMessage(value.ToString()+ "\n");
        }
    }
}
