#ifndef _OBJFWD_H
#define _OBJFWD_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

#include <basetyps.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef _COM_interface IMoniker *LPMONIKER;
typedef _COM_interface IStream *LPSTREAM;
typedef _COM_interface IMarshal *LPMARSHAL;
typedef _COM_interface IMalloc *LPMALLOC;
typedef _COM_interface IMallocSpy *LPMALLOCSPY;
typedef _COM_interface IMessageFilter *LPMESSAGEFILTER;
typedef _COM_interface IPersist *LPPERSIST;
typedef _COM_interface IPersistStream *LPPERSISTSTREAM;
typedef _COM_interface IRunningObjectTable *LPRUNNINGOBJECTTABLE;
typedef _COM_interface IBindCtx *LPBINDCTX,*LPBC;
typedef _COM_interface IAdviseSink *LPADVISESINK;
typedef _COM_interface IAdviseSink2 *LPADVISESINK2;
typedef _COM_interface IDataObject *LPDATAOBJECT;
typedef _COM_interface IDataAdviseHolder *LPDATAADVISEHOLDER;
typedef _COM_interface IEnumMoniker *LPENUMMONIKER;
typedef _COM_interface IEnumFORMATETC *LPENUMFORMATETC;
typedef _COM_interface IEnumSTATDATA *LPENUMSTATDATA;
typedef _COM_interface IEnumSTATSTG *LPENUMSTATSTG;
typedef _COM_interface IEnumSTATPROPSTG LPENUMSTATPROPSTG;
typedef _COM_interface IEnumString *LPENUMSTRING;
typedef _COM_interface IEnumUnknown *LPENUMUNKNOWN;
typedef _COM_interface IStorage *LPSTORAGE;
typedef _COM_interface IPersistStorage *LPPERSISTSTORAGE;
typedef _COM_interface ILockBytes *LPLOCKBYTES;
typedef _COM_interface IStdMarshalInfo *LPSTDMARSHALINFO;
typedef _COM_interface IExternalConnection *LPEXTERNALCONNECTION;
typedef _COM_interface IRunnableObject *LPRUNNABLEOBJECT;
typedef _COM_interface IROTData *LPROTDATA;
typedef _COM_interface IPersistFile *LPPERSISTFILE;
typedef _COM_interface IRootStorage *LPROOTSTORAGE;
typedef _COM_interface IRpcChannelBuffer *LPRPCCHANNELBUFFER;
typedef _COM_interface IRpcProxyBuffer *LPRPCPROXYBUFFER;
typedef _COM_interface IRpcStubBuffer *LPRPCSTUBBUFFER;
typedef _COM_interface IPropertyStorage *LPPROPERTYSTORAGE;
typedef _COM_interface IEnumSTATPROPSETSTG *LPENUMSTATPROPSETSTG;
typedef _COM_interface IPropertySetStorage *LPPROPERTYSETSTORAGE;
typedef _COM_interface IClientSecurity *LPCLIENTSECURITY;
typedef _COM_interface IServerSecurity *LPSERVERSECURITY;
typedef _COM_interface IClassActivator *LPCLASSACTIVATOR;
typedef _COM_interface IFillLockBytes *LPFILLLOCKBYTES;
typedef _COM_interface IProgressNotify *LPPROGRESSNOTIFY;
typedef _COM_interface ILayoutStorage *LPLAYOUTSTORAGE;
#ifdef __cplusplus
}
#endif
#endif
