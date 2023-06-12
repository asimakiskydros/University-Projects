# Request-Reply-Messaging-App-Communication-Networks-Project

Project header:

Create a server-client messaging system that uses a simple request-reply protocol. You may implement it using
sockets or the built in RMI technology Java provides (in this project, RMI was used). Clients should send 
requests to the server and it should send back a response and terminate the connection.

At the bare minimum, the app should have the following:

1. Class Message(boolean isRead, String sender, String receiver, String body, int messageID)
2. Class Account(String username, int authToken, List<Message> inbox)
3. Class Server, to be invoked as "java Server <port number>" through the command line, implemented using the
   RMI template.
4. Class Client, to be invoked as "java Client <host ip> <port number> <FN_ID> <args>" through the command line,
   implemented using the RMI template.
5. Function Create Account, accessed through the "java Client <host ip> <port number> 1 <username>" command, that 
   returns a unique authToken on success and appropriate error messages on invalid username format or username unavailability.
6. Function Show Accounts, accessed through the "java Client <host ip> <port number> 2 <authToken>" command, that 
   lists all the registered accounts on success and returns an error message on invalid authToken.
7. Function Send Message, accessed through the "java Client <host ip> <port number> 3 <authToken> <recipient> <message body>"
   command, that adds a message with <message body> as body to the recipient's inbox and returns "OK" on success and returns 
   appropriate error messages on invalid authToken and non-existent recipient.
8. Function Show Inbox, accessed through the "java Client <host ip> <port number> 4 <authToken>" command, that lists
   the user's inbox with the following format: <messageID_n>. from:<username_n>[\*] (\* signifies the message is unread) on success
   and returns an error message on invalid authToken.
9. Function Read Message, accessed through the "java Client <host ip> <port number> 5 <authToken> <messageID>" command, that
   prints the selected message on the users screen and then marks it as read on success and returns appropriate error messages
   on invalid authToken and non-existent messageID.
10. Function Delete Message, accessed through the "java Client <host ip> <port number> 6 <authToken> <messageID>" command, that
   deletes the corresponding message from the user's inbox and returns "OK" on success and returns appropriate error messages
   on invalid authToken and non-existent messageID.
  
  The original header in greek can be found in the pdf of this repository, courtesy of Aristotle University of Thessalonica, CSD.
