using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class NameMessage : MonoBehaviour
{
    public Text info;
    public Text readName;

    const string roomNameChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int roomNameLength = 4;

    public GameObject startMenu;
    public GameObject connectionMenu;
    public GameObject createGameButton;
    public GameObject joinGameButton;
    public GameObject confirmUsernameButton;
    public InputField nameInputField;
    private void Awake()
    {
        if (PhotonNetwork.playerName != "")
        {
            connectionMenu.SetActive(true);
            startMenu.SetActive(false);
            nameInputField.text = PhotonNetwork.playerName;
            createGameButton.SetActive(true);
            joinGameButton.SetActive(true);
            confirmUsernameButton.SetActive(false); 
            info.gameObject.SetActive(true);
            info.text = "Your username is now " + PhotonNetwork.playerName;
        }
    }

    public void showMessage()
    {
        info.gameObject.SetActive(true);
        info.text = "Your username is now " + readName.text;
        PhotonNetwork.playerName = readName.text;
    }

    public void CreateGame()
    {
        string roomName = "";
        for (int i = 0; i < roomNameLength; i++)
        {
            roomName += roomNameChars[Random.Range(0, roomNameChars.Length - 1)];
        }
        Debug.Log("Room Name " + roomName);
        PhotonNetwork.CreateRoom(roomName, new RoomOptions() { MaxPlayers = 4 }, null);
        //SceneManager.LoadScene(2);
    }

    private void OnJoinedRoom()
    {
        Debug.Log("Joined room " + PhotonNetwork.room.Name);
        SceneManager.LoadScene(2);

    }
}
