#!/usr/bin/env bash

# invokes make and copies web assets into the data directory
# for lantern's http server.
# assumes that the web assets have been built, of course.
# to build them, install a recen verion
make
echo "[lantern-server]: Building web assets."
cd ../lantern-web-client && npm install && npm run-script build
echo "Copying web client into data dir."
cd $OLDPWD
mkdir -p ./data/http-docs
cp ../lantern-web-client/build/* ./data/http-docs
