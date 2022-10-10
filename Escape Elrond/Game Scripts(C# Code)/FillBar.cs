using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FillBar : MonoBehaviour
{

    // Unity UI References
    public Slider slider;
    public Text displayLevel;
    public int lvl = 1;

    // Create a property to handle the slider's value
    private float currentValue = 0f;
    public float CurrentValue
    {
        get
        {
            return currentValue;
        }
        set
        {
            currentValue = value;
            slider.value = currentValue;
            displayLevel.text = lvl.ToString();
            // displayText.text = (slider.value * 100).ToString("0.00") + "%";
        }
    }

    // Use this for initialization
    void Start()
    {
        CurrentValue = 0f;
    }

    // Update is called once per frame
    void Update()
    {
        // CurrentValue += 0.0043f;
        CurrentValue += 10.0f;
    }
}