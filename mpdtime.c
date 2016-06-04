#include <mpd/status.h>
#include <mpd/connection.h>
#include <stdio.h>

int main()
{
	unsigned time = 0;
	unsigned total_time = 0;
	struct mpd_connection *conn;
	struct mpd_status *status;
	enum mpd_state state;

	conn = mpd_connection_new(NULL, 0, 0);
	status = mpd_run_status(conn);

	if (!status)
		return 0;

	time = mpd_status_get_elapsed_time(status);
	total_time = mpd_status_get_total_time(status);
	state = mpd_status_get_state(status);
	mpd_status_free(status);
	mpd_connection_free(conn);

	if (state > 1) {
		switch(state) {
			case MPD_STATE_UNKNOWN:
				printf("%s", "(unknown) ");
				break;
			case MPD_STATE_STOP:
				printf("%s", "(stopped) ");
				break;
			case MPD_STATE_PLAY:
				break;
			case MPD_STATE_PAUSE:
				printf("%s", "(paused) ");
				break;
			default:
				printf("%s", "(ERROR) ");
				break;
		}
		//printf("%s/%s\n", convert(time), convert(total_time));

		int elapsed_seconds = time % 60;
		int elapsed_minutes = time / 60;

		int seconds = total_time % 60;
		int minutes = total_time / 60;

		int percent_done = time / (double)total_time * 100;
		//printf("%d\n%d\n", time, total_time);
		//printf("%d\n", percent_done);

		printf("%u:%02u/%u:%02u (%d%%)", elapsed_minutes, elapsed_seconds, minutes, seconds, percent_done);
		//printf("%u:%02u", elapsed_minutes, elapsed_seconds);
	}

	return 0;
}
