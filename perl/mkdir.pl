use constant GET_ADPATER_DIR => "/tmp/getadapter/1";
use File::Path;
if ( ! -d GET_ADPATER_DIR) {
    mkpath(GET_ADPATER_DIR);
}
