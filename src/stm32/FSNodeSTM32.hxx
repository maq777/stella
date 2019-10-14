#ifndef FS_NODE_STM32_HXX
#define FS_NODE_STM32_HXX

#include "FSNode.hxx"

/*
 * Implementation of the Stella file system API based on STM32 API.
 *
 * Parts of this class are documented in the base interface class,
 * AbstractFSNode.
 */
class FilesystemNodeSTM32 : public AbstractFSNode
{
  public:
    FilesystemNodeSTM32();

    explicit FilesystemNodeSTM32(const string& path);

    bool exists() const override;
    const string& getName() const override    { return _name; }
    void setName(const string& name) override { _name = name; }
    const string& getPath() const override { return _path; }
    string getShortPath() const override;
    bool hasParent() const override { return false; }
    bool isDirectory() const override { return _isDirectory; }
    bool isFile() const override      { return _isFile;      }
    bool isReadable() const override;
    bool isWritable() const override;
    bool makeDir() override;
    bool rename(const string& newfile) override;

    bool getChildren(AbstractFSList& list, ListMode mode) const override;
    AbstractFSNodePtr getParent() const override;

    uInt32 read(ByteBuffer& image) const override;

  protected:
    string _name;
    string _path;
    bool _isDirectory;
    bool _isFile;
    bool _isPseudoRoot;
    bool _isValid;
};

#endif
