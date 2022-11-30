// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/jvm/jre-11-openjdk/lib/server/:/home/ujoimro/doc/university/sje/2022-11-21_kalocsanyi_daniel/jsvm/jsvm/target

package site.selyerobotics.jdlib;

public class JDlib {

    static {
        System.loadLibrary("libJDlib");
    }

    public static class Native {
        protected long NativeHandle = 0;
    }

    public static class Matrix extends Native implements AutoCloseable {

        public Matrix(int row, int col) {
            init(row, col);
        }

        public Matrix() {
            init();
        }

        private native void init();

        private native void init(int row, int col);

        public native void set(int row, int col, double val);

        public native double get(int row, int col);

        public native void Dispose();

        public native int nc();

        public native int nr();

        @Override
        public void close() throws Exception {
            Dispose();
        }

        @Override
        public String toString() {
            String result = new String();
            result += "[ \n";
            for (int row = 0; row < nr(); row++) {
                result += "[ ";
                for (int col = 0; col < nc() - 1; col++) {
                    result += get(row, col) + ", ";
                }
                result += get(row, nc() - 1) + " ]\n";
            }
            result += "]\n";

            return result;
        }
    };

    public static class LearnedFunction extends Native implements AutoCloseable {
        public LearnedFunction() {
            init();
        }

        private native void init();

        public native double Evaluate(Matrix sample);

        public native void SetNormalizer(VectorNormalizer normalizer);

        public native void SetFunction(DecisionFunction func);

        public native long BasisVectorsSize();

        public native void Dispose();

        @Override
        public void close() throws Exception {
            Dispose();
        }
    };

    public static native ProbabilisticDecisionFunction TrainProbabilisticDecisionFunction2(SVMNuTrainer trainer,
            VectorM samples,
            Vectord labels,
            long fold);

    public static native ProbabilisticDecisionFunction TrainProbabilisticDecisionFunction3(
            ReducedDecisionFunctionTrainer2 trainer, VectorM samples,
            Vectord labels,
            long fold);

    public static class NormalizedProbabilisticFunction extends Native implements AutoCloseable {
        public NormalizedProbabilisticFunction() {
            init();
        }

        private native void init();

        public native double Evaluate(Matrix sample);

        public native void SetNormalizer(VectorNormalizer normalizer);

        public native void SetFunction(ProbabilisticDecisionFunction func);

        public native long BasisVectorsSize();

        public native void Dispose();

        @Override
        public void close() throws Exception {
            Dispose();
        }
    };

    public static class RBF extends Native implements AutoCloseable {

        public RBF(double gamma) {
            init(gamma);
        }

        public native void init(double gamma);

        public native void Dispose();

        @Override
        public void close() throws Exception {
            Dispose();
        }
    };

    public static class DecisionFunction extends Native implements AutoCloseable {
        public DecisionFunction() {
            init();
        }

        public native double Evaluate(Matrix sample);

        private native void init();

        public native void Dispose();

        @Override
        public void close() throws Exception {
            Dispose();
        }
    }

    public static class ProbabilisticDecisionFunction extends Native implements AutoCloseable {
        public ProbabilisticDecisionFunction() {
            init();
        }

        public native double Evaluate(Matrix sample);

        private native void init();

        public native void Dispose();

        @Override
        public void close() throws Exception {
            Dispose();
        }
    }

    public static class SVMNuTrainer extends Native implements AutoCloseable {
        public SVMNuTrainer() {
            init();
        }

        private native void init();

        public native void SetKernel(RBF Kernel);

        public native void SetNu(double nu);

        public native DecisionFunction Train(VectorM samples, Vectord labels);

        public native void Dispose();

        @Override
        public void close() throws Exception {
            Dispose();
        }
    }

    public static class ReducedDecisionFunctionTrainer2 extends Native implements AutoCloseable {
        public ReducedDecisionFunctionTrainer2() {
            init();
        }

        private native void init();

        public native void Dispose();

        public native DecisionFunction Train(VectorM samples, Vectord labels);

        @Override
        public void close() throws Exception {
            Dispose();
        }
    }

    static public native ReducedDecisionFunctionTrainer2 Reduced2(
            SVMNuTrainer trainer,
            long num_bv,
            double eps);

    static public native void RandomizeSamples(VectorM samples, Vectord labels);

    static public native double MaximumNu(Vectord labels);

    static public native Matrix CrossValidateTrainer(SVMNuTrainer trainer, VectorM samples, Vectord labels,
            long fold);

    static public native Matrix CrossValidateTrainerReduced(ReducedDecisionFunctionTrainer2 trainer, VectorM samples,
            Vectord labels,
            long fold);

    public static class Vectord extends Native implements AutoCloseable {

        public Vectord() {
            init();
        }

        private native void init();

        public native void Add(double value);

        public native long Size();

        public native double Get(long index);

        public native void Set(long index, double value);

        public native void Dispose();

        @Override
        public void close() throws Exception {
            Dispose();
        }
    };

    public static class VectorM extends Native implements AutoCloseable {

        public VectorM() {
            init();
        }

        private native void init();

        public native void Add(Matrix value);

        public native long Size();

        public native Matrix Get(long index);

        public native void Set(long index, Matrix value);

        public native void Dispose();

        @Override
        public void close() throws Exception {
            Dispose();
        }
    };

    public static class VectorNormalizer extends Native implements AutoCloseable {
        public VectorNormalizer() {
            init();
        }

        private native void init();

        public native void Train(VectorM samples);

        public native Matrix Normalize(Matrix sample);

        public native void Dispose();

        @Override
        public void close() throws Exception {
            Dispose();
        }
    };

    public static native void SerializeLearnedFunction(String fileName, LearnedFunction function);

    public static native void SerializeNormalizedProbabilisticFunction(String fileName,
            NormalizedProbabilisticFunction function);

    public static native void DeserializeLearnedFunction(String fileName, LearnedFunction function);

    public static native void DeserializeNormalizedProbabilisticFunction(String fileName,
            NormalizedProbabilisticFunction function);
}
