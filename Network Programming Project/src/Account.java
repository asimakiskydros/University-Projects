import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Account implements Serializable {
    private final String username;
    private int messagesCounter;
    private final List<Message> messageBox;
    private final int authToken;

    public Account(String username, int authToken){
        this.username = username;
        this.authToken = authToken;
        this.messageBox = new ArrayList<>();

        this.messagesCounter = 0;
    }
    public void addMessage(Message message){
        this.messageBox.add(message);
        this.messagesCounter++;
    }
    public boolean removeMessage(int messageID){
        //search for the message by comparing ids
        //if found, remove it from inbox
        for(Message msg : this.messageBox) if (msg.getMessageID() == messageID) {
            this.messageBox.remove(msg);
            return true;
        }
        return false;
    }
    public String getUsername(){
        return this.username;
    }
    public List<Message> getMessageBox() {
        return messageBox;
    }
    public int getMessagesCounter() {
        return messagesCounter;
    }
}
