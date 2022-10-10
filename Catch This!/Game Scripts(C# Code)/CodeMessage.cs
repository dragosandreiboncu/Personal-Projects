using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class CodeMessage : MonoBehaviour
{
    public Text readName;
    public GameObject info;

    public void showMessage()
    {
        /*
        if (readName.text != "SALUT")
            info.SetActive(true);
        else
        {
            SceneManager.LoadScene("Lobby", LoadSceneMode.Additive);
            GameObject.Find("CanvasUI").SetActive(false);
            GameObject.Find("EventSystemUI").SetActive(false);
            MainScript.leader = false;
        }
        */
    }

    public void JoinGame()
    {
        RoomOptions roomOptions = new RoomOptions();
        roomOptions.MaxPlayers = 4;
        PhotonNetwork.JoinRoom(readName.text.ToUpper());
    }

    private void OnJoinedRoom()
    {
        Debug.Log("Joined room " + PhotonNetwork.room.Name);
        SceneManager.LoadScene(2);
        GameObject.Find("CanvasUI").SetActive(false);
        GameObject.Find("EventSystemUI").SetActive(false);

    }

    private void OnPhotonJoinRoomFailed()
    {
        Debug.Log("Join room failed");
        info.SetActive(true);
    }
}
