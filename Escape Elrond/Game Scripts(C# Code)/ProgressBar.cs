using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class ProgressBar : FillBar
{

    // Event to invoke when the progress bar fills up
    private UnityEvent onProgressComplete;
    public GameObject xpBarUI;
    public float CurrentValue;

    void Start()
    {
        // Initialize onProgressComplete and set a basic callback
        if (onProgressComplete == null)
            onProgressComplete = new UnityEvent();
        onProgressComplete.AddListener(OnProgressComplete);
    }

    void Update()
    {
        base.CurrentValue = CurrentValue;
        if (CurrentValue >= slider.maxValue)
        {
            onProgressComplete.Invoke();
            slider.maxValue += 100;
        }
    }

    // The method to call when the progress bar fills up
    void OnProgressComplete()
    {
        lvl++;
        CurrentValue = 0;
        //displayLevel.text = lvl.ToString();
    }

    public void SetA(bool val)
    {
        xpBarUI.SetActive(val);
    }
}