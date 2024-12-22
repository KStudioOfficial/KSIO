#include "MainComponent.h"
#include "helpers.h"

//==============================================================================
MainComponent::MainComponent() : webView{
    juce::WebBrowserComponent::Options{}
    .withResourceProvider([this](const auto& url){
        return getResource(url);
    })
    .withNativeIntegrationEnabled()
    .withInitialisationData("testDataField", "test data value")
} {
    addAndMakeVisible(webView);
    webView.goToURL(webView.getResourceProviderRoot());
    
    addAndMakeVisible(runJavascriptButton);
    runJavascriptButton.onClick = [this] {
        static const juce::Identifier EVENT_ID{"exampleEvent"};
        webView.emitEventIfBrowserIsVisible(EVENT_ID, 42);
        
//        constexpr auto JAVASCRIPT_TO_RUN{"console.log(\"WHAT THE SIGMA\")"};
//        webView.evaluateJavascript(
//                                   JAVASCRIPT_TO_RUN,
//                                   [](juce::WebBrowserComponent::EvaluationResult result) {
//                                       if (const auto* resultPtr = result.getResult()) {
//                                           std::cout << "JS evaluation result: " << resultPtr->toString() << std::endl;
//                                       } else {
//                                           std::cout << "JS evaluation failed: " << result.getError()->message << std::endl;
//                                       }
//                                   }
//        );
    };
    
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds();
    webView.setBounds(bounds.removeFromRight(getWidth() / 2));
    runJavascriptButton.setBounds(bounds.removeFromTop(50).reduced(5));
}
