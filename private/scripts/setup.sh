#!/bin/sh

# We default to local but check params so we can allow a specific environment to
# be passed in.
DRUSH='drush'
ENV='local'
SITE='site-short-name'
USER='make-me-not-admin'
PASSWORD='make-me-random-and-secure'
SITE_NAME='My Wonderful Site'
SITE_PROFILE='standard'

if [ ! -z "$1" ]; then
  DRUSH="drush @$SITE.$1"
fi

${DRUSH} si $SITE_PROFILE \
  --account-name=$USER \
  --account-pass=$PASSWORD \
  --site-name=$SITE_NAME -y

# No golive exists and tag_dev shouldn't be run on live.
if [ "$ENV" != 'live' ]; then
  ${DRUSH} en tag_dev -y
  ${DRUSH} go${ENV}
fi

${DRUSH} uli
