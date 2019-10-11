//============================================================================
//
//   SSSS    tt          lll  lll
//  SS  SS   tt           ll   ll
//  SS     tttttt  eeee   ll   ll   aaaa
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2019 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef FS_NODE_ZIP_HXX
#define FS_NODE_ZIP_HXX

#include "ZipHandler.hxx"
#include "FSNode.hxx"

/*
 * Implementation of the Stella file system API based on ZIP archives.
 * ZIP archives are treated as directories if the contain more than one ROM
 * file, as a file if they contain a single ROM file, and as neither if the
 * archive is empty.  Hence, if a ZIP archive isn't a directory *or* a file,
 * it is invalid.
 *
 * Parts of this class are documented in the base interface class, AbstractFSNode.
 */
class FilesystemNodeZIP : public AbstractFSNode
{
  public:
    /**
     * Creates a FilesystemNodeZIP with the root node as path.
     */
    FilesystemNodeZIP();

    /**
     * Creates a FilesystemNodeZIP for a given path.
     *
     * @param path  String with the path the new node should point to.
     */
    explicit FilesystemNodeZIP(const string& path);

    bool exists() const override     { return _realNode && _realNode->exists(); }
    const string& getName() const override { return _name;      }
    const string& getPath() const override { return _path;      }
    string getShortPath() const   override { return _shortPath; }
    bool isDirectory() const override { return _isDirectory; }
    bool isFile() const      override { return _isFile;      }
    bool isReadable() const  override { return _realNode && _realNode->isReadable(); }
    bool isWritable() const  override { return false; }

    //////////////////////////////////////////////////////////
    // For now, ZIP files cannot be modified in any way
    bool makeDir() override { return false; }
    bool rename(const string& newfile) override { return false; }
    //////////////////////////////////////////////////////////

    bool getChildren(AbstractFSList& list, ListMode mode, bool hidden) const override;
    AbstractFSNodePtr getParent() const override;

    uInt32 read(BytePtr& image) const override;

  private:
    FilesystemNodeZIP(const string& zipfile, const string& virtualpath,
        AbstractFSNodePtr realnode, bool isdir);

    void setFlags(const string& zipfile, const string& virtualpath,
        AbstractFSNodePtr realnode);

    friend ostream& operator<<(ostream& os, const FilesystemNodeZIP& node)
    {
      os << "_zipFile:     " << node._zipFile << endl
         << "_virtualPath: " << node._virtualPath << endl
         << "_path:        " << node._path << endl
         << "_shortPath:   " << node._shortPath << endl;
      return os;
    }

  private:
    /* Error types */
    enum zip_error
    {
      ZIPERR_NONE = 0,
      ZIPERR_NOT_A_FILE,
      ZIPERR_NOT_READABLE,
      ZIPERR_NO_ROMS
    };

    AbstractFSNodePtr _realNode;
    string _zipFile, _virtualPath;
    string _name, _path, _shortPath;
    zip_error _error;
    uInt32 _numFiles;

    bool _isDirectory, _isFile;

    // ZipHandler static reference variable responsible for accessing ZIP files
    static unique_ptr<ZipHandler> myZipHandler;

    // Get last component of path
    static const char* lastPathComponent(const string& str)
    {
      if(str.empty())
        return "";

      const char* start = str.c_str();
      const char* cur = start + str.size() - 2;

      while (cur >= start && !(*cur == '/' || *cur == '\\'))
        --cur;

      return cur + 1;
    }
};

#endif
