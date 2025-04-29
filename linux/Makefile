all: send_signal catch_signal send_message receive_message

send_signal: send_signal.c
	$(CC) send_signal.c -o send_signal

catch_signal: catch_signal.c
	$(CC) catch_signal.c -o catch_signal

send_message: send_message.c
	$(CC) send_message.c -o send_message

receive_message: receive_message.c
	$(CC) receive_message.c -o receive_message

clean: 
	$(RM) send_signal catch_signal send_message receive_message
