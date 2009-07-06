if (Drupal.jsEnabled) {
  $(document).ready(function() {
    $('#migration_start_monitor').click(function(){
      $.getJSON('/admin/settings/migration/start_monitor', function(json) {
        alert(json.response);
      });
    });
    $('#migration_stop_monitor').click(function(){
      $.getJSON('/admin/settings/migration/stop_monitor', function(json) {
        alert(json.response);
      });
    });
  })
}
