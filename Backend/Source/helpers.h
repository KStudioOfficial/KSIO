/*
  ==============================================================================

    helpers.h
    Created: 21 Dec 2024 8:38:07pm
    Author:  Kimi Weng

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using Resource = juce::WebBrowserComponent::Resource;

std::optional<Resource> getResource(const juce::String& url);
