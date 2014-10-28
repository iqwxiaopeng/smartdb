// 0 : reached EOF
// > 0 : bytes read
size_t read_records(const StorageEngine &storage, Buffer &buf) {
  ssize_t ret = storage.read_records(buf);
  if (ret < 0) {
    perror();
    exit(1);
  }
  return ret;
}