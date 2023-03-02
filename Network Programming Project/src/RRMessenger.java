import java.rmi.*;
import java.util.ArrayList;

public interface RRMessenger extends Remote{
    /**
     * createAccount:
     * Checks username for correctness and uniqueness. If it qualifies on both, it creates a new account and binds it
     * with a unique 4-digit authID.
     * @param username the given username for the new account
     * @return a unique authID if successful; 0 if the user already exists; -1 if the username is invalid.
     * @throws RemoteException concerns Remote
     */
    int createAccount(String username)
            throws RemoteException; // 1
    /**
     * showAccounts:
     * Checks authToken for validity. If valid, returns a formatted list of all registered accounts.
     * @param authToken the unique id of the requester
     * @return a formatted list of all registered accounts, if id is valid; null otherwise.
     * @throws RemoteException concerns Remote
     */
    ArrayList<String> showAccounts(int authToken)
            throws RemoteException; // 2
    /**
     * sendMessage:
     * Checks authToken for validity. If valid, sends a message to recipient with the given body.
     * @param authToken the unique id of the requester
     * @param recipient the third party who will receive the message
     * @param messageBody the body of the message
     * @return "OK" if successful; "Invalid Auth Token" if authToken is invalid; "User does not exist" if
     *         recipient is an unknown username.
     * @throws RemoteException concerns Remote
     */
    String sendMessage(int authToken, String recipient, String messageBody)
            throws RemoteException; // 3
    /**
     * showInbox:
     * Checks authToken for validity. If valid, returns a formatted list of the requester's inbox.
     * @param authToken the unique id of the requester
     * @return a formatted list of the requester's inbox if id is valid; null otherwise.
     * @throws RemoteException concerns Remote
     */
    ArrayList<String> showInbox(int authToken)
            throws RemoteException; // 4
    /**
     * readMessage:
     * Checks authToken and messageID for validity. If they are both valid,
     * returns the display of the message in question, along with the username of the sender.
     * @param authToken the unique id of the requester
     * @param messageID the id of the message the requester wishes to read
     * @return the display of the message to be printed if successful;
     *         "MessageID does not exist" if the id given doesn't correspond to a message the user has received;
     *         null otherwise.
     * @throws RemoteException concerns Remote
     */
    String readMessage(int authToken, int messageID)
            throws RemoteException; // 5
    /**
     * deleteMessage:
     * Checks authToken and messageID for validity. If both are valid, deletes the corresponding message from the
     * requester's inbox.
     * @param authToken the unique id of the requester
     * @param messageID the id of the message the requester wishes to delete from their inbox
     * @return "OK" if successful; "Message does not exist" if the id given doesn't correspond to a message the user
     *          has received; null otherwise.
     * @throws RemoteException concerns Remote
     */
    String deleteMessage(int authToken, int messageID)
            throws RemoteException; // 6
}
