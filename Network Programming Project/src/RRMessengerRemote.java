import java.rmi.*;
import java.rmi.server.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Objects;
import java.util.Random;

public class RRMessengerRemote extends UnicastRemoteObject implements RRMessenger {
    private final HashMap<Integer, Account> accounts;

    //manually request a list of just the existing usernames every time it is needed, so as not to have
    //the same information stored multiple times at all instances.
    private ArrayList<String> getUniqueUsernames(){
        ArrayList<String> uniqueUsernames = new ArrayList<>();
        for(Account account : accounts.values())
            uniqueUsernames.add(account.getUsername());

        return uniqueUsernames;
    }

    RRMessengerRemote() throws RemoteException{
        super();
        this.accounts = new HashMap<>();
    }

    public int createAccount(String username) throws RemoteException{
        System.out.println("\n->Client request: create account with given username: \"" + username + "\"");
        int id = -1;
        //test given username for uniqueness and correct format
        //accept only usernames with latin characters, numbers and/or '_'
        if(username == null || username.isBlank()) {
            System.out.println("<-Request denied, given username is invalid");
            return id;
        }
        for(char letter : username.toCharArray())
            if (letter != '_' &&
               (letter < '0' ||
                letter > 'z' ||
               (letter > '9' && letter < 'A') ||
               (letter > 'Z' && letter < 'a') )
            ) {
                System.out.println("<-Request denied, given username is invalid");
                return id;
            }
        if(getUniqueUsernames().contains(username)){
            System.out.println("<-Request denied, given username already exists");
            return 0;
        }
        //from this point onwards, the given username is presumed correct
        //for the token, keep generating random 4-digit ids until you stumble upon an original one
        //lazy approach but the chances that this runs for more than 2 loops are < 1/100000000
        Random rand = new Random();
        do{
          id = rand.nextInt(9000) + 1000;
        } while(accounts.containsKey(id));

        accounts.put(id, new Account(username, id));
        System.out.println("<-Request accepted. Account created successfully, returning auth id " + id);
        return id;
    } // operation #1

    public ArrayList<String> showAccounts(int authToken) throws RemoteException{
        System.out.println("\n->Client#" + authToken + " request: show registered accounts");
        //check given token validity
        if (!accounts.containsKey(authToken)){
            System.out.println("<-Request denied, given authenticator token wasn't found");
            return null;
        }
        ArrayList<String> template = new ArrayList<>();
        long i = 1;
        //list existing accounts in format "n. <username_n>\n"
        ArrayList<String> uniqueUsernames = getUniqueUsernames();
        if(uniqueUsernames.size() > 0)
            for(String username : uniqueUsernames) template.add( i++ +". " + username);

        System.out.println("<-Request accepted, returning account database");
        return template;
    } // operation #2

    public String sendMessage(int authToken, String recipient, String messageBody) throws RemoteException{
        System.out.println("\n->Client#" + authToken + " request: send message to user \"" + recipient + "\"");
        //check given token validity
        if (!accounts.containsKey(authToken)){
            System.out.println("<-Request denied, given authenticator token wasn't found");
            return "Invalid Auth Token";
        }
        //check recipient existence
        if (!getUniqueUsernames().contains(recipient)){
            System.out.println("<-Request denied, recipient user doesn't exist");
            return "User does not exist";
        }
        //search of the recipient and, when found, send him the message
        for(Account account : accounts.values())
            if(Objects.equals(account.getUsername(), recipient)){
                String sender = accounts.get(authToken).getUsername();
                int messageID = accounts.get(authToken).getMessagesCounter() + 1;
                account.addMessage(
                        new Message(false, sender, recipient, messageID, messageBody)
                );
                break;
            }

        System.out.println("<-Request accepted. Message sent to user \"" + recipient + "\", returning confirmation");
        return "OK";
    } // operation #3

    public ArrayList<String> showInbox(int authToken) throws RemoteException{
        System.out.println("\n->Client#" + authToken + " request: show inbox");
        //check given token validity
        if (!accounts.containsKey(authToken)) {
            System.out.println("<-Request denied, given authenticator token wasn't found");
            return null;
        }
        //list messages in format "<message_id_n>. from: <sender_n_username>(message read ? \n : *\n)"
        ArrayList<String> template = new ArrayList<>();
        for(Message msg: accounts.get(authToken).getMessageBox())
            template.add(msg.getMessageID() + ". from: " + msg.getSender() + (msg.getStatus() ? "" : "*") );

        System.out.println("<-Request accepted, returning client inbox");
        return template;
    } // operation #4

    public String readMessage(int authToken, int messageID) throws RemoteException{
        System.out.println("\n->Client#" + authToken + " request: read message with given id " + messageID);
        //check given token validity
        if (!accounts.containsKey(authToken)){
            System.out.println("<-Request denied, given authenticator token wasn't found");
            return null;
        }
        //search for message with given id
        //if found, print it in format (<sender_username>)<body>\n
        //if not, inform id is wrong/nonexistent
        for(Message msg : accounts.get(authToken).getMessageBox())
            if (msg.getMessageID() == messageID) {
                msg.setStatus(true);
                System.out.println("<-Request accepted, returning body of message with id " + messageID);
                return "(" + msg.getSender() + ")" + msg.getBody();
            }

        System.out.println("<-Request denied, given id " + messageID + " does not correlate with a message this user has");
        return "Message ID does not exist\n";
    } // operation #5

    public String deleteMessage(int authToken, int messageID) throws RemoteException{
        System.out.println("\n->Client#" + authToken + " request: delete message with given id " + messageID);
        //check given token validity
        if (!accounts.containsKey(authToken)){
            System.out.println("<-Request denied, given authenticator token wasn't found");
            return null;
        }
        if (accounts.get(authToken).removeMessage(messageID)){
            System.out.println("<-Request accepted, deleting message and returning confirmation");
            return "OK";
        }
        else{
            System.out.println("<-Request denied, given id " + messageID + " does not correlate with a message this user has");
            return "Message does not exist";
        }
    } // operation #6
}
