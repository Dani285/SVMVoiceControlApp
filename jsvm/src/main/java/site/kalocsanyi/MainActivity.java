package site.kalocsanyi;

import fr.delthas.javamp3.Sound;

import java.io.File;
import java.io.IOException;
import java.io.*;
import java.lang.reflect.Field;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class MainActivity {
    SVMModel svm_model = new SVMModel();
    File file = new File("C:/Users/kaloc/Desktop/Java/audio1.mp3");

    public MainActivity() {

    }

    byte[] getSamples() throws IOException {
        Path audiopath = Paths.get("C:/Users/kaloc/Desktop/Java/audio1.mp3");
        try (Sound sample_sound = new Sound(new BufferedInputStream(Files.newInputStream(audiopath)))) {
            System.out.println(sample_sound.getSamplingFrequency());
            byte[] samples = sample_sound.readAllBytes();
            return samples;
        }
    }

    public static double[] toDouble(byte[] byte_array) throws IOException {
        // Path audiopath = Paths.get("C:/Users/kaloc/Desktop/Java/audio1.mp3");
        // Sound sample_sound = new Sound(new
        // BufferedInputStream(Files.newInputStream(audiopath)));
        // System.out.println(sample_sound.getSamplingFrequency());
        // double[] darray = new double[byte_array.length/2];
        double[] darray = new double[byte_array.length / 2]; // need to make sure we are going through the whole array
        for (int dNum = 0; dNum < darray.length / 2; dNum++) {
            darray[dNum] = byte_array[2 * dNum] + byte_array[2 * dNum + 1] << 8; // Start with the integer = 0
        }
        return darray;
    }

    static {
        System.loadLibrary("JDlib");
    }

    public static void main(String[] args) throws IOException {
        // svm_model.Build();
        // recognize words from audio file
        // System.setProperty("java.library.path","C:/Program
        // Files/Java/jdk-15.0.1/bin");
        Path audiopath = Paths.get("C:/Users/kaloc/Desktop/Corpus/Clips/common_voice_en_21875014.mp3");
        Sound sample_sound = new Sound(new BufferedInputStream(Files.newInputStream(audiopath)));
        System.out.println(sample_sound.getSamplingFrequency());

        String paths = "C:/Users/kaloc/Desktop/Corpus/Clips/common_voice_en_21875014.mp3";
        byte[] samples;
        try (FileInputStream fis = new FileInputStream(paths)) {
            samples = sample_sound.readAllBytes(); // alternative to use function for getting samples
            fis.read(samples, 0, 32);
        }
        System.out.println("length = " + samples.length); // "length = " + samples.lengtj
        double[] dsamples = toDouble(samples);
        // XYSeries graph = new XYSeries("Chart");
        // XYDataset xyDataset = new XYSeriesCollection(graph); //used for display graph
        // using JFreeChart library
        // JFreeChart chart = ChartFactory.createXYLineChart(
        // "Chart", "Hz", "Data",
        // xyDataset, PlotOrientation.VERTICAL, true, true, false);
        // ChartFrame graphFrame = new ChartFrame("Chart", chart);
        // graphFrame.setVisible(true);
        // graphFrame.setSize(400, 400);
        // _Fourier fourier = new DiscreteFourier(dsamples);
        // fourier.transform();
        // boolean onlyPositive = true;
        // double[] out = fourier.getMagnitude(onlyPositive);
        DiscreteFourierTransform discreteFourierTransform = new DiscreteFourierTransform();
        var out = discreteFourierTransform.Transform();
        System.out.println("out.length = " + out.length);

        final Field sysPathsField;
        try {
            sysPathsField = ClassLoader.class.getDeclaredField("C:/Program Files/Java/jdk-15.0.1/bin");
            sysPathsField.setAccessible(true);
            try {
                sysPathsField.set(null, null);
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        } catch (NoSuchFieldException e) {
            e.printStackTrace();
        }
        // Files.copy(sample_sound,
        // Paths.get("C:/Users/kaloc/Desktop/Java/audio3.raw"));

        var samples2 = new SVMModel.VectorM();

        var labels = new SVMModel.Vectord();

        var samp = new SVMModel.Matrix(dsamples.length, 1);
        for (int i = 0; i < dsamples.length; i++) {
            samp.set(i, 0, dsamples[i]);
        }
        samples2.Add(samp);
        labels.Add(+1);

        // Here we normalize all the samples by subtracting their mean and dividing by
        // their standard deviation. This is generally a good idea since it often
        // heads off numerical stability problems and also prevents one large feature
        // from smothering others. Doing this doesn't matter much in this example so
        // I'm just doing this here so you can see an easy way to accomplish this with
        // the library.
        var normalizer = new SVMModel.VectorNormalizer();

        // let the normalizer learn the mean and standard deviation of the samples
        normalizer.Train(samples2);

        // now normalize each sample
        for (long i = 0; i < samples2.Size(); ++i) {

            var sample = samples2.Get(i);

            var normalized = normalizer.Normalize(sample);

            samples2.Set(i, normalized);

        }

        // Now that we have some data we want to train on it. However, there are two
        // parameters to the training. These are the nu and gamma parameters. Our
        // choice for these parameters will influence how good the resulting decision
        // function is. To test how good a particular choice of these parameters is
        // we can use the cross_validate_trainer() function to perform n-fold cross
        // validation on our training data. However, there is a problem with the way
        // we have sampled our distribution above. The problem is that there is a
        // definite ordering to the samples. That is, the first half of the samples
        // look like they are from a different distribution than the second half. This
        // would screw up the cross validation process but we can fix it by
        // randomizing the order of the samples with the following function call.
        SVMModel.RandomizeSamples(samples2, labels);

        // The nu parameter has a maximum value that is dependent on the ratio of the
        // +1 to -1 labels in the training data. This function finds that value.
        final double max_nu = SVMModel.MaximumNu(labels);

        // here we make an instance of the svm_nu_trainer object that uses our kernel
        // type.
        var trainer = new SVMModel.SVMNuTrainer();

        // Now we loop over some different nu and gamma values to see how good they
        // are. Note that this is a very simple way to try out a few possible
        // parameter choices. You should look at the model_selection_ex.cpp program
        // for examples of more sophisticated strategies for determining good
        // parameter choices.
        System.out.println("doing cross validation");
        for (double gamma = 0.00001; gamma <= 1; gamma *= 5) {
            for (double nu = 0.00001; nu < max_nu; nu *= 5) {
                // tell the trainer the parameters we want to use
                trainer.SetKernel(new SVMModel.RBF(gamma));
                trainer.SetNu(nu);

                System.out.println("gamma: " + gamma + "    nu: " + nu);
                // Print out the cross validation accuracy for 3-fold cross validation
                // using the current gamma and nu. cross_validate_trainer() returns a row
                // vector. The first element of the vector is the fraction of +1 training
                // examples correctly classified and the second number is the fraction of
                // -1 training examples correctly classified.
                System.out.println("     cross validation accuracy: "
                        + SVMModel.CrossValidateTrainer(trainer, samples2, labels, 3));
            }
        }

        // From looking at the output of the above loop it turns out that a good value
        // for nu and gamma for this problem is 0.15625 for both. So that is what we
        // will use.

        // Now we train on the full set of data and obtain the resulting decision
        // function. We use the value of 0.15625 for nu and gamma. The decision
        // function will return values
        // >= 0 for samples it predicts are in the +1 class and numbers < 0 for
        // samples it predicts to be in the -1 class.
        trainer.SetKernel(new SVMModel.RBF(0.15625));
        trainer.SetNu(0.15625);

        // Here we are making an instance of the normalized_function object. This
        // object provides a convenient way to store the vector normalization
        // information along with the decision function we are going to learn.
        try (var learned_function = new SVMModel.LearnedFunction()) {
            learned_function.SetNormalizer(normalizer); // save normalization information
            learned_function.SetFunction(trainer.Train(samples2, labels)); // perform the actual SVM training and save
                                                                           // the
            // results

            // print out the number of support vectors in the resulting decision function
            System.out.println("\nnumber of support vectors in our learned_function is "
                    + learned_function.BasisVectorsSize());

            // Now let's try this decision_function on some samples we haven't seen
            // before.
            var sample = new SVMModel.Matrix(dsamples.length, 1);
            for (int i = 0; i < dsamples.length; i++) {
                sample.set(i, 0, dsamples[i]);
            }
            System.out.println("This is a +1 class example, the classifier output is "
                    + learned_function.Evaluate(sample));

            System.out.println("This is a +1 class example, the classifier output is "
                    + learned_function.Evaluate(sample));
            for (int j = 0; j < dsamples.length; j++) {

                sample.set(j, 0, dsamples[j]);
                sample.set(j, 0, dsamples[j]);
            }
            System.out.println("This is a -1 class example, the classifier output is "
                    + learned_function.Evaluate(sample));
            for (int v = 0; v < dsamples.length; v++) {
                sample.set(v, 0, dsamples[v]);
                sample.set(1, 0, 0);
            }
            System.out.println("This is a -1 class example, the classifier output is "
                    + learned_function.Evaluate(sample));

            // We can also train a decision function that reports a well conditioned
            // probability instead of just a number > 0 for the +1 class and < 0 for the
            // -1 class. An example of doing that follows:
            // using probabilistic_funct_type =
            // dlib::probabilistic_decision_function<kernel_type>;
            // using pfunct_type = dlib::normalized_function<probabilistic_funct_type>;

            var learned_pfunct = new SVMModel.NormalizedProbabilisticFunction();
            learned_pfunct.SetNormalizer(normalizer);
            var probabilisticDecisionFunction = SVMModel.TrainProbabilisticDecisionFunction2(trainer, samples2, labels,
                    3);
            learned_pfunct.SetFunction(probabilisticDecisionFunction);

            // Now we have a function that returns the probability that a given sample is
            // of the +1 class.

            // print out the number of support vectors in the resulting decision function.
            // (it should be the same as in the one above)
            System.out.println(
                    "\nnumber of support vectors in our learned_pfunct is " + learned_pfunct.BasisVectorsSize());

            sample.set(0, 0, 3.123);
            sample.set(1, 0, 2);
            System.out.println(
                    "This +1 class example should have high probability.  Its probability is: "
                            + learned_pfunct.Evaluate(sample));

            sample.set(0, 0, 3.123);
            sample.set(1, 0, 9.3545);
            System.out.println(
                    "This +1 class example should have high probability.  Its probability is: "
                            + learned_pfunct.Evaluate(sample));

            sample.set(0, 0, 13.123);
            sample.set(1, 0, 9.3545);
            System.out.println(
                    "This -1 class example should have low probability.  Its probability is: "
                            + learned_pfunct.Evaluate(sample));

            sample.set(0, 0, 13.123);
            sample.set(1, 0, 0);
            System.out.println(
                    "This -1 class example should have low probability.  Its probability is: "
                            + learned_pfunct.Evaluate(sample));

            // Another thing that is worth knowing is that just about everything in dlib
            // is serializable. So for example, you can save the learned_pfunct object to
            // disk and recall it later like so:

            SVMModel.SerializeNormalizedProbabilisticFunction("saved_function.dat", learned_pfunct);

            // Now let's open that file back up and load the function object it contains.
            SVMModel.DeserializeNormalizedProbabilisticFunction("saved_function.dat", learned_pfunct);

            // Note that there is also an example program that comes with dlib called the
            // file_to_code_ex.cpp example. It is a simple program that takes a file and
            // outputs a piece of C++ code that is able to fully reproduce the file's
            // contents in the form of a std::string object. So you can use that along
            // with the std::istringstream to save learned decision functions inside your
            // actual C++ code files if you want.

            // Lastly, note that the decision functions we trained above involved well
            // over 200 basis vectors. Support vector machines in general tend to find
            // decision functions that involve a lot of basis vectors. This is
            // significant because the more basis vectors in a decision function, the
            // longer it takes to classify new examples. So dlib provides the ability to
            // find an approximation to the normal output of a trainer using fewer basis
            // vectors.

            // Here we determine the cross validation accuracy when we approximate the
            // output using only 10 basis vectors. To do this we use the reduced2()
            // function. It takes a trainer object and the number of basis vectors to use
            // and returns a new trainer object that applies the necessary post
            // processing
            // during the creation of decision function objects.
            System.out.println(
                    "\ncross validation accuracy with only 10 support vectors: " +
                            SVMModel.CrossValidateTrainerReduced(SVMModel.Reduced2(trainer, 10, 1e-3), samples2,
                                    labels, 3));

            // Let's print out the original cross validation score too for comparison.
            System.out.println(
                    "cross validation accuracy with all the original support vectors: " +
                            SVMModel.CrossValidateTrainer(trainer, samples2, labels, 3));

            // When you run this program you should see that, for this problem, you can
            // reduce the number of basis vectors down to 10 without hurting the cross
            // validation accuracy.

            // To get the reduced decision function out we would just do this:
            learned_function.SetFunction(SVMModel.Reduced2(trainer, 10, 1e-3).Train(samples2,
                    labels));

            // And similarly for the probabilistic_decision_function:
            learned_pfunct
                    .SetFunction(SVMModel.TrainProbabilisticDecisionFunction3(SVMModel.Reduced2(trainer, 10, 1e-3),
                            samples2, labels, 3));
        } catch (Exception ex) {
            System.out.println(ex.toString());
        }
    }
}
